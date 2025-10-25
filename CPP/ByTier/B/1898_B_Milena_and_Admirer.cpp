// Problem: CF 1898 B - Milena and Admirer
// https://codeforces.com/contest/1898/problem/B

/*
B. Milena and Admirer
Algorithms/Techniques: Greedy approach with reverse iteration.
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing the array.

The problem asks to make an array non-decreasing by splitting elements into two parts.
We use a greedy approach:
- Traverse from right to left.
- For each element that breaks the non-decreasing property,
  we split it such that the new value is as small as possible to reduce operations.
- The number of operations needed is accumulated.

This solution simulates the reverse process: instead of splitting and increasing array size,
we track how many times we need to "undo" a violation by effectively decreasing elements.
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
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    ll cnt(0);
    for (ll p = n - 1; p > 0; p--) {
      // Calculate how many times we must split v[p-1] to make it <= v[p]
      ll d = (v[p - 1] + (v[p] - 1)) / v[p];
      cnt += (d > 0 ? d : 1) - 1;  // Add number of operations needed
      v[p - 1] /= d;               // Update the value after splitting
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/