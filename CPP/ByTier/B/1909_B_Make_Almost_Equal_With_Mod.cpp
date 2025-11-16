// Problem: CF 1909 B - Make Almost Equal With Mod
// https://codeforces.com/contest/1909/problem/B

/*
 * Code Purpose: 
 *   Given an array of distinct positive integers, find a value of k (1 <= k <= 10^18) 
 *   such that when each element of the array is replaced by a[i] % k, the resulting 
 *   array contains exactly 2 distinct values.
 *   
 * Algorithm:
 *   - Try powers of 2 (2, 4, 8, 16, ...) as potential values of k.
 *   - For each k, compute the remainders of all array elements modulo k.
 *   - If the number of distinct remainders is exactly 2, return that k.
 *   - Since it's guaranteed there's always a solution, the loop will terminate.
 *
 * Time Complexity: O(log(10^18) * n) = O(60 * n) = O(n)
 * Space Complexity: O(n) due to the set storing up to 3 distinct remainders.
 */

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll mod(0);  // Stores the result k value
    for (ll t = 2; !mod && t < 3e18; t *= 2) {  // Try increasing powers of 2
      std::set<ll> s;
      for (ll p = 0; s.size() < 3 && p < n; p++) {
        s.insert(a[p] % t);  // Insert remainder into set
      }
      if (s.size() == 2) {   // If exactly 2 distinct remainders found
        mod = t;
        break;
      }
    }
    printf("%lld\n", mod);
  }
}


// https://github.com/VaHiX/CodeForces/