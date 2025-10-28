// Problem: CF 2006 F - Dora's Paint
// https://codeforces.com/contest/2006/problem/F

/*
 * Problem: F. Dora's Paint
 * Algorithm: Graph partitioning, combinatorics, inclusion-exclusion
 * Time Complexity: O(n log n + n^2) where n is the size of matrix
 * Space Complexity: O(n^2) for storing matrix structure
 * 
 * Approach:
 * 1. The matrix is divided into rows and columns as connected components.
 * 2. Each column is represented by a vector of row indices where it has '1'.
 * 3. The beauty of a matrix is computed based on valid operations to reach that matrix.
 * 4. For each possible mistake (one element is wrong), we compute expected beauty,
 *    considering all possible true matrices.
 * 5. The key part is to compute the number of valid ways to achieve a particular matrix
 *    through row/col operations.
 */

#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;
#define ll long long int
#define mod 998244353
struct mint {
  int _x;
  mint() {}
  mint(int a) {
    _x = a;
    if (_x >= mod)
      _x -= mod;
  }
  mint(ll a) { _x = a % mod; }
};
mint operator+(mint a, mint b) {
  a._x += b._x;
  if (a._x >= mod)
    a._x -= mod;
  return a;
}
mint operator-(mint a, mint b) {
  a._x -= b._x;
  if (a._x < 0)
    a._x += mod;
  return a;
}
mint operator*(mint a, mint b) {
  a._x = (ll)a._x * b._x % mod;
  return a;
}
mint operator+=(mint &a, mint b) {
  a._x += b._x;
  if (a._x >= mod)
    a._x -= mod;
  return a;
}
mint operator-=(mint &a, mint b) {
  a._x -= b._x;
  if (a._x < 0)
    a._x += mod;
  return a;
}
mint operator*=(mint &a, mint b) {
  a._x = (ll)a._x * b._x % mod;
  return a;
}
mint pow(mint a, int b) {
  mint c = 1;
  while (b > 0) {
    if (b & 1)
      c *= a;
    a *= a;
    b >>= 1;
  }
  return c;
}
mint inv(mint a) { return pow(a, mod - 2); }
mint fac[200002], ifac[200002];
mint C(int a, int b) {
  if (b < 0 || b > a)
    return 0;
  return fac[a] * ifac[b] * ifac[a - b];
}
void initC(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = fac[i - 1] * i;
  ifac[n] = inv(fac[n]);
  for (int i = n; i >= 1; i--)
    ifac[i - 1] = ifac[i] * i;
}
#include <vector>

int T, n, m;
int siz[200000];
vector<int> vec[200000];
int id[200000];
int vis[200000];
int val[400000];
bool comp(int a, int b) { return siz[a] > siz[b]; }
int diff(int a, int b) {
  int res = -1;
  for (int i = 0; i < siz[a]; i++)
    vis[vec[a][i]]++;
  for (int i = 0; i < siz[b]; i++)
    if (vis[vec[b][i]] == 0)
      res = vec[b][i];
  for (int i = 0; i < siz[a]; i++)
    vis[vec[a][i]]--;
  return res;
}
void modify(int x, int y) {
  for (int i = 0; i < siz[x]; i++)
    if (vec[x][i] == y) {
      swap(vec[x][i], vec[x][siz[x] - 1]);
      vec[x].pop_back();
      siz[x]--;
      return;
    }
  vec[x].push_back(y);
  siz[x]++;
  return;
}
mint solve_single(void) {
  sort(id, id + n, comp);
  for (int i = 1; i < n; i++)
    if (diff(id[i - 1], id[i]) != -1)
      return 0;
  mint res = 1;
  int lst = n, len = 0;
  for (int i = 0; i < n; i++) {
    if (lst > siz[id[i]]) {
      res *= fac[len] * fac[lst - siz[id[i]]];
      len = 1;
      lst = siz[id[i]];
    } else
      len++;
  }
  if (lst > 0)
    res *= fac[len];
  return res;
}
mint solve(void) {
  for (int i = 0; i < n; i++)
    id[i] = i;
  sort(id, id + n, comp);
  int xa = -1, ya, xb, yb;
  for (int i = 1; i < n; i++) {
    xb = id[i];
    yb = diff(id[i - 1], id[i]);
    if (yb != -1) {
      xa = id[i - 1];
      ya = diff(id[i], id[i - 1]);
      break;
    }
  }
  mint res = 0;
  if (xa == -1) {
    mint base = solve_single();
    int lst = n, len = 0, k = 0;
    for (int i = 0; i < n; i++) {
      if (lst > siz[id[i]]) {
        if (len > 0) {
          val[k] = len;
          k++;
        }
        val[k] = lst - siz[id[i]];
        k++;
        len = 1;
        lst = siz[id[i]];
      } else
        len++;
    }
    val[k] = len;
    k++;
    if (lst > 0) {
      val[k] = lst;
      k++;
    }
    for (int i = 1; i < k; i++)
      if (val[i - 1] > 0 && val[i] > 0) {
        mint x = base;
        if (i >= 2 && val[i - 1] == 1)
          x *= val[i - 2] + 1;
        if (i + 2 < k && val[i] == 1)
          x *= val[i + 1] + 1;
        if (i == k - 1)
          x *= val[i];
        res += x;
      }
  } else {
    modify(xa, ya);
    res += solve_single();
    modify(xa, ya);
    modify(xa, yb);
    res += solve_single();
    modify(xa, yb);
    modify(xb, ya);
    res += solve_single();
    modify(xb, ya);
    modify(xb, yb);
    res += solve_single();
    modify(xb, yb);
  }
  return res;
}
int main(void) {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    initC(n);
    for (int i = 0; i < n; i++) {
      vec[i].clear();
      siz[i] = 0;
    }
    while (m--) {
      int x, y;
      scanf("%d%d", &x, &y);
      x--;
      y--;
      siz[y]++;  // Column y has '1' in row x
      vec[y].push_back(x);
    }
    mint ans = solve() * inv(n) * inv(n);
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/