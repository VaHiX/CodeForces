// Problem: CF 1899 B - 250 Thousand Tons of TNT
// https://codeforces.com/contest/1899/problem/B

/*
B. 250 Thousand Tons of TNT

Problem Description:
Given n boxes with weights a[i], we want to distribute them into trucks such that each truck holds exactly k boxes (k must be a divisor of n).
The goal is to maximize the absolute difference between the maximum and minimum total weights of trucks.

Approach:
- Use prefix sums for efficient subarray sum calculation.
- For every possible number of trucks k (which means every divisor of n), we compute 
  the total weight of each group of k boxes and find max - min among these groups.
- Optimization: only check divisors up to sqrt(n) and their corresponding pairs.

Time Complexity: O(n * sqrt(n)) per test case
Space Complexity: O(n)
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n + 1, 0); // Prefix sum array
    ll mn(1e17 + 7), mx(0);      // Min and max of current group sums
    for (ll p = 1; p <= n; p++) {
      ll x;
      scanf("%lld", &x);
      mn = (mn < x ? mn : x);           // Update global min weight
      mx = (mx > x ? mx : x);           // Update global max weight
      a[p] = a[p - 1] + x;              // Build prefix sum
    }
    ll res = mx - mn;                   // Base case: when k = n (one truck)
    
    // Check all divisors of n up to sqrt(n)
    for (ll r = 2; r * r <= n; r++) {
      if (n % r) {                      // If r is not a divisor
        continue;
      }
      
      // Case 1: Group size = r, num trucks = n / r
      ll step = r;
      mn = 1e17 + 7;
      mx = 0;
      for (ll p = r; p <= n; p += r) {
        ll cur = a[p] - a[p - r];       // Sum of subarray from (p - r + 1) to p
        mn = (mn < cur ? mn : cur);     // Update minimum group sum
        mx = (mx > cur ? mx : cur);     // Update maximum group sum
      }
      ll tmp = mx - mn;                 // Difference for this grouping
      res = (res > tmp ? res : tmp);    // Keep track of max difference

      // Case 2: Group size = n / r, num trucks = r
      step = n / r;
      mn = 1e17;
      mx = 0;
      for (ll p = step; p <= n; p += step) {
        ll cur = a[p] - a[p - step];    // Same sum calculation but different grouping
        mn = (mn < cur ? mn : cur);
        mx = (mx > cur ? mx : cur);
      }
      tmp = mx - mn;
      res = (res > tmp ? res : tmp);    // Update max difference again
    }
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/