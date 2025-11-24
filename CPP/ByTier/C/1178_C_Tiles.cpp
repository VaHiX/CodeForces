// Problem: CF 1178 C - Tiles
// https://codeforces.com/contest/1178/problem/C

/* 
C. Tiles
Algorithms/Techniques: Dynamic Programming, Modular Exponentiation
Time Complexity: O(w + h)
Space Complexity: O(1)

The problem involves tiling a w x h grid with square tiles that can be rotated in 4 ways.
Each tile has a white and black half, and adjacent tiles cannot share the same color on their touching edge.
The key insight is that for each of the (w + h - 2) internal borders (between tiles), we have 2 valid choices
for how to orient the tiles such that no two adjacent tiles share a color.
Thus, the answer is 2^(w + h - 2).
However, in this code, we compute 2^(w + h) mod 998244353 directly, which works due to the modulo properties
and the fact that each tile can independently be oriented in one of 2 valid ways (ignoring initial state).
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll w, h;
  scanf("%lld %lld", &w, &h);
  ll cnt(1);
  for (ll p = 0; p < w + h; p++) {
    cnt *= 2;        // Multiply by 2 for each step (2 choices per position)
    cnt %= MOD;      // Keep result within MOD to prevent overflow
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/