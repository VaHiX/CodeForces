// Problem: CF 1703 F - Yet Another Problem About Pairs Satisfying an Inequality
// https://codeforces.com/contest/1703/problem/F

/*
F. Yet Another Problem About Pairs Satisfying an Inequality
Algorithm: Two-pointer / Prefix Sum approach
Time Complexity: O(n) per test case
Space Complexity: O(n) due to vector v

Problem: Count pairs (i,j) such that a[i] < i < a[j] < j.
This is solved by preprocessing the array and using prefix sums to efficiently count valid pairs.
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
    std::vector<ll> v(n + 1, 0); // Prefix sum array to store count of valid a[i] < i
    ll total(0); // Total number of valid pairs
    for (ll p = 1; p <= n; p++) {
      ll x;
      scanf("%lld", &x);
      v[p] = v[p - 1]; // Carry forward previous prefix sum
      if (x < p) {     // If a[p] < p, it's a valid candidate for left side of pair
        ++v[p];        // Increment count at position p
        total += (x ? v[x - 1] : 0); // Add number of valid pairs ending at this point
      }
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/