// Problem: CF 2073 D - Tower of Hanoi
// https://codeforces.com/contest/2073/problem/D

/*
 * Code Purpose:
 *   This program solves an extended version of the Tower of Hanoi problem,
 *   where each disk has an initial rod assignment and we are to compute
 *   the number of steps required to move all disks of a given range to rod 1.
 *   It uses a segment tree with lazy propagation for dynamic updates and queries,
 *   with states managed through a state machine that tracks transitions between rods.
 *
 * Algorithms/Techniques:
 *   - Segment Tree with Range Updates
 *   - Dynamic Programming with Memoization in Segment Tree Nodes
 *   - Modular Exponentiation
 *   - Bit Manipulation (XOR operations for rod transitions)
 *
 * Time Complexity:
 *   - Preprocessing (Building Tree): O(n)
 *   - Each Update Operation: O(log n)
 *   - Each Query Operation: O(log n)
 *   - Total Time Complexity: O(n + q * log n)
 *
 * Space Complexity:
 *   - Segment Tree Storage: O(n)
 *   - Additional Arrays: O(n)
 *   - Total Space Complexity: O(n)
 */

#include <iostream>

#define N 100005
#define M 505
#define LL long long
#define inf 2147483647
#define LD long double
#define eps 1e-6
using namespace std;
int n, m, a[N], f[N << 2][3], g[N << 2][3], pw[N], inv[N], F[3], G[3];
const int p = 998244353;

// Fast exponentiation for modular arithmetic
inline int P(int x, int y) {
  int z = 1;
  while (y) {
    if (y & 1)
      z = 1ll * z * x % p;
    y >>= 1, x = 1ll * x * x % p;
  }
  return z;
}

// Add operation with modulo handling
inline void A(int &x, int y) {
  x += y, (x >= p) && (x -= p, 0), (x < 0) && (x += p, 0);
}

// Multiply operation with modulo handling
inline void mul(int &x, int y) { x = 1ll * x * y % p; }

// Push Up: Update parent node state based on child nodes
inline void PU(int x) {
  for (int i = 0; i ^ 3; i++)
    g[x][i] = g[x << 1][g[x << 1 | 1][i]],
    f[x][i] = (f[x << 1][g[x << 1 | 1][i]] + f[x << 1 | 1][i]) % p;
}

// Build: Initialize leaf nodes and recursively build up the segment tree
inline void B(int x, int l, int r) {
  if (l == r) {
    for (int i = 0; i ^ 3; i++)
      if (i == a[l])
        g[x][i] = i, f[x][i] = 0;
      else
        g[x][i] = (3 ^ i ^ a[l]), f[x][i] = pw[l];
    return;
  }
  int mid = (l + r) >> 1;
  B(x << 1, l, mid), B(x << 1 | 1, mid + 1, r), PU(x);
}

// Update: Modify value at index y to z and update the segment tree
inline void U(int x, int l, int r, int y, int z) {
  if (l == r) {
    a[l] = z;
    for (int i = 0; i ^ 3; i++)
      if (i == a[l])
        g[x][i] = i, f[x][i] = 0;
      else
        g[x][i] = (3 ^ i ^ a[l]), f[x][i] = pw[l];
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= y)
    U(x << 1, l, mid, y, z);
  else
    U(x << 1 | 1, mid + 1, r, y, z);
  PU(x);
}

// Query: Traverse segment tree to collect results for interval [ll, rr]
inline void Q(int x, int l, int r, int ll, int rr) {
  if (l >= ll && r <= rr) {
    for (int i = 0; i ^ 3; i++)
      G[i] = (F[g[x][i]] + f[x][i]) % p;
    for (int i = 0; i ^ 3; i++)
      F[i] = G[i];
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= ll)
    Q(x << 1, l, mid, ll, rr);
  if (mid < rr)
    Q(x << 1 | 1, mid + 1, r, ll, rr);
}

// Main solve function to process all queries
inline void solve(int tc) {
  cin >> n >> m;
  pw[0] = 1, inv[0] = 1, inv[1] = P(2, p - 2);
  for (int i = 1; i <= n; i++)
    cin >> a[i], a[i]--, pw[i] = 2 * pw[i - 1] % p,
                         inv[i] = 1ll * inv[i - 1] * inv[1] % p;
  B(1, 1, n);
  while (m--) {
    char op;
    int x, y;
    cin >> op >> x >> y;
    if (op == 'c')
      U(1, 1, n, x, y - 1);
    else
      F[0] = F[1] = F[2] = 0, Q(1, 1, n, x, y),
      cout << 1ll * F[0] * inv[x] % p << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tc = 1;
  while (tc--)
    solve(tc);
  return 0;
}


// https://github.com/VaHiX/codeForces/