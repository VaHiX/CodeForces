// Problem: CF 1795 E - Explosions?
// https://codeforces.com/contest/1795/problem/E

/*
Algorithm: Dynamic Programming with Monotonic Stack
Purpose: Find the minimum MP to kill all monsters using basic spells and one explosion spell with chaining effects.
The problem involves optimally choosing a monster to explode, then calculating how much damage needs to be dealt to monsters
before the explosion to prevent chain reactions from killing too many monsters. 

Time Complexity: O(n) amortized per test case due to monotonic stack operations.
Space Complexity: O(n) for storing arrays and intermediate computations.

Approach:
- Precompute prefix sums of healths for efficient range sum queries.
- Use monotonic stacks to efficiently compute minimum damage needed from left and right sides for each potential explosion point.
- For each monster, compute the minimum MP needed if that monster is the one to explode.
- The final answer is the minimum across all possible explosion points.

*/

#include <cstdio>
const int rSiz = 1 << 21;
char rBuf[rSiz], *p1 = rBuf, *p2 = rBuf;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = rBuf) + fread(rBuf, 1, rSiz, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
template <class T> void rd(T &x) {
  char ch = gc();
  for (; ch < '0' || ch > '9'; ch = gc())
    ;
  for (x = 0; ch >= '0' && ch <= '9'; ch = gc())
    x = (x << 1) + (x << 3) + (ch ^ 48);
}
#include <algorithm>
const int _ = 3e5 + 5;
int n, a[_], b[_], c[_];
long long f[_], g[_], d[_], ans;
void solve() {
  rd(n);
  for (int i = 1; i <= n; i++)
    rd(a[i]), d[i] = d[i - 1] + a[i]; // Precompute prefix sums
  for (int i = 1; i <= n; i++) {
    f[i] = 0, b[i] = i; // 'b' maintains the leftmost position for monotonic stack
    // While the current element can be merged with previous elements due to explosion effects
    for (; b[i] > 1 && a[i] - (i - b[i] + 1) <= a[b[i] - 1];) {
      // Add cost of previous explosion effect and compute contribution
      f[i] += f[b[i] - 1] + 1ll * (a[b[i] - 1] - (a[i] - (i - b[i] + 1))) *
                                (b[i] - b[b[i] - 1]);
      b[i] = b[b[i] - 1]; // Update the stack pointer
    }
    // If damage exceeds health, adjust the segment to be killed before explosion
    if (a[i] - (i - b[i] + 1) < 0) {
      b[i] = std::max(i - a[i], 1);
      f[i] = d[i] - d[b[i] - 1] - 1ll * a[i] * (a[i] + 1) / 2;
    }
  }
  g[n + 1] = 0;
  for (int i = n; i; i--) {
    g[i] = 0, c[i] = i;
    for (; c[i] < n && a[i] - (c[i] - i + 1) <= a[c[i] + 1];) {
      // Similar logic for right side
      g[i] += g[c[i] + 1] + 1ll * (a[c[i] + 1] - (a[i] - (c[i] - i + 1))) *
                                (c[c[i] + 1] - c[i]);
      c[i] = c[c[i] + 1];
    }
    if (a[i] - (c[i] - i + 1) < 0) {
      c[i] = std::min(i + a[i], n);
      g[i] = d[c[i]] - d[i - 1] - 1ll * a[i] * (a[i] + 1) / 2;
    }
  }
  // Final adjustments for stack updates
  ans = 1e18;
  for (int i = 1; i <= n; i++)
    if (b[i] > 1 && a[i] - (i - b[i] + 1) > 0)
      f[i] += f[b[i] - 1], b[i] = b[b[i] - 1];
  for (int i = n; i; i--)
    if (c[i] < n && a[i] - (c[i] - i + 1) > 0)
      g[i] += g[c[i] + 1], c[i] = c[c[i] + 1];
  // Calculate final cost for each possible explosion point
  for (int i = 1; i <= n; i++) {
    ans = std::min(ans, a[i] + f[i] + g[i] + d[b[i] - 1] + d[n] - d[c[i]]);
  }
  printf("%lld\n", ans);
}
int main() {
  int T;
  rd(T);
  for (; T; T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/