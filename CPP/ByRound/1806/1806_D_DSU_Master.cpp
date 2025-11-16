// Problem: CF 1806 D - DSU Master
// https://codeforces.com/contest/1806/problem/D

/*
 * Problem: D. DSU Master
 * 
 * Purpose:
 *   This solution computes the sum of values over all permutations of length k
 *   for each k from 1 to n-1, where the value of a permutation is defined by
 *   a specific directed graph construction process involving DSU (Disjoint Set Union)
 *   and edge directions based on array `a`.
 *
 * Algorithm:
 *   Uses dynamic programming with precomputed values:
 *   - f[i]: sum of values for all permutations of length i
 *   - g[i]: auxiliary factor used in transitions
 *   Transitions are based on the value of a[i] (0 or 1), affecting whether
 *   edges go forward or backward.
 *
 * Time Complexity: O(n)
 *   Each test case processes elements in linear time, and total operations
 *   across all test cases are bounded by 5 * 10^5.
 *
 * Space Complexity: O(n)
 *   Space used for arrays f, g, and input a.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 5e5 + 5, mod = 998244353;
void chkmax(int &x, int y) { x = max(x, y); }
void chkmin(int &x, int y) { x = min(x, y); }
void Add(int &x, int y) { x += y, x %= mod; }
int ab(int x) {
  if (x < 0)
    x = -x;
  return x;
}
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch - '0'), ch = getchar();
  return x * f;
}
int n, a[N], f[N], g[N];
signed main(void) {
  int T = read();
  while (T--) {
    n = read();
    for (int i = 1; i < n; i++)
      a[i] = read();
    f[1] = g[1] = 1;
    for (int i = 2; i < n; i++) {
      if (!a[i])
        g[i] = 1ll * g[i - 1] * i % mod, // update g[i] with multiplication by i
        f[i] = (1ll * f[i - 1] * (i - 1) + f[i - 1] + g[i - 1]) % mod; // transition for case a[i]==0
      else
        f[i] = 1ll * f[i - 1] * i % mod, g[i] = 1ll * g[i - 1] * (i - 1) % mod; // transition for case a[i]==1
    }
    for (int i = 1; i < n; i++)
      printf("%d ", f[i] * (a[1] ^ 1)); // output result scaled by (a[1] xor 1)
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/