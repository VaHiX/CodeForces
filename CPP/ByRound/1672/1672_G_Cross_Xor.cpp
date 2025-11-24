// Problem: CF 1672 G - Cross Xor
// https://codeforces.com/contest/1672/problem/G

/*
Purpose: 
This code solves the "Cross Xor" problem where we are given a grid with some elements fixed as 0, 1, or '?'.
We can perform operations that flip all elements in a row or column. The goal is to count how many ways
we can fill the '?' entries such that the resulting grid is achievable through valid operations.

Algorithms/Techniques:
1. Union-Find (Disjoint Set Union) - to group rows and columns related through '?' entries.
2. Graph-based reasoning on XOR constraints.
3. Modular arithmetic for large results.
4. Special handling based on parity of rows/columns.

Time Complexity: O(r * c * α(r + c)) where α is inverse Ackermann function, effectively almost constant.
Space Complexity: O(r * c) for storing the grid and auxiliary data structures.

*/
#include <stdlib.h>
#include <initializer_list>
#include <iostream>
#include <utility>

#define int long long
using namespace std;
const int N = 2e3 + 5, M = N * N, H = 998244353;
char a[N][N], b[N][N];
int pw[M], n, m, ans;
inline void solve1() {
  // For grids where number of rows is even, handle special case with all ? filled
  for (int c = 0; c < 2; ++c) {
    int res = 1;
    for (int i = 1; i <= n; ++i) {
      int cnt = 0, v = c;
      for (int j = 1; j <= m; ++j)
        if (a[i][j] != '?')
          v ^= (a[i][j] - '0');
        else
          ++cnt;
      if (!cnt && v)
        res = 0;
      else if (cnt)
        res = res * pw[cnt - 1] % H;
    }
    ans = (ans + res) % H;
  }
  cout << ans << "\n", exit(0);
}
int f[N << 1], val[N << 1], E[N << 1], sz[N << 1];
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
inline void mer(int a, int b) {
  // Union two nodes and track edges and value differences
  a = find(a), b = find(b);
  if (a == b)
    ++E[a];
  else
    f[a] = b, E[b] += E[a] + 1, sz[b] += sz[a], val[b] ^= val[a];
}
inline int solve(int r, int c) {
  // Compute constraints based on fixed values for given row/column parity
  for (int i = 1; i <= n; ++i) {
    int cnt = 0, v = r;
    for (int j = 1; j <= m; ++j)
      if (a[i][j] != '?')
        v ^= (a[i][j] - '0');
      else
        ++cnt;
    if (!cnt && v)
      return 0;
    val[i] = v;
  }
  for (int j = 1; j <= m; ++j) {
    int cnt = 0, v = c;
    for (int i = 1; i <= n; ++i)
      if (a[i][j] != '?')
        v ^= (a[i][j] - '0');
      else
        ++cnt;
    if (!cnt && v)
      return 0;
    val[j + n] = v;
  }
  // Initialize union-find structure
  for (int i = 1; i <= n + m; ++i)
    f[i] = i, sz[i] = 1, E[i] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (a[i][j] == '?')
        mer(i, j + n);
  int res = 1;
  for (int i = 1; i <= n + m; ++i)
    if (find(i) == i) {
      if (val[i])
        return 0;
      res = res * pw[E[i] - (sz[i] - 1)] % H;
    }
  return res;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> m, pw[0] = 1;
  // Precompute powers of 2 modulo H
  for (int i = 1; i <= n * m; ++i)
    pw[i] = pw[i - 1] * 2 % H;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> a[i][j];
  // Special handling for even rows or columns
  if (!(n & 1) && !(m & 1)) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        cnt += (a[i][j] == '?');
    cout << pw[cnt] << "\n", exit(0);
  }
  if (!(n & 1))
    solve1();
  if (!(m & 1)) {
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        b[i][j] = a[i][j];
    swap(n, m);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        a[i][j] = b[j][i];
    solve1();
  }
  for (int r : {0, 1})
    for (int c : {0, 1})
      ans = (ans + solve(r, c)) % H;
  cout << ans << "\n";
}


// https://github.com/VaHiX/CodeForces/