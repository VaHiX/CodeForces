// Problem: CF 1472 A - Cards for Friends
// https://codeforces.com/contest/1472/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll w, h, n;
    scanf("%lld %lld %lld", &w, &h, &n);
    ll s = w * h; // Total initial area
    ll cnt(1);    // Maximum number of pieces we can get from one sheet
    // Keep dividing the area by 2 as long as it's even
    while (s % 2 == 0) {
      cnt *= 2;   // Double the number of pieces
      s /= 2;     // Halve the area
    }
    puts(cnt >= n ? "YES" : "NO"); // Check if we can get enough pieces
  }
}
/*
Problem: Cards for Friends

Purpose:
This code determines whether a sheet of paper of size w x h can be cut into at least n pieces,
following specific cutting rules. The key insight is to find the maximum number of pieces
that can be obtained by repeatedly halving either width or height (whenever even).

Algorithms/Techniques:
- Mathematical analysis of how many times a rectangle can be halved
- Prime factorization approach for powers of 2 only

Time Complexity: O(log(max(w,h))) per test case
Space Complexity: O(1)

The algorithm works by computing how many times we can divide the total area w*h by 2,
which corresponds to the maximum number of pieces obtainable.
*/


// https://github.com/VaHiX/codeForces/