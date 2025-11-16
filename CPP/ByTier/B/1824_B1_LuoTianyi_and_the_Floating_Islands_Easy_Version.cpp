// Problem: CF 1824 B1 - LuoTianyi and the Floating Islands (Easy Version)
// https://codeforces.com/contest/1824/problem/B1

/*
Code Purpose:
This program calculates the expected number of "good" islands when k people are randomly placed on k distinct islands in a tree structure. A good island is one with the minimum total distance to all k people. The solution uses tree traversal and combinatorics to count configurations efficiently.

Algorithms/Techniques:
- DFS traversal to compute subtree sizes
- Combinatorial mathematics for counting valid placements
- Modular arithmetic for handling large numbers and modular inverse

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by:
1. Building the tree from input edges
2. Using DFS to calculate subtree sizes
3. For each edge, calculating how many ways k people can be placed such that the edge splits the tree into two parts, each containing exactly k/2 people (for even k)
4. Using combinatorics to compute the expected value by dividing by total ways to place k people

Note: This implementation assumes k is even. When k is odd, it simply returns 1.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target(                                                            \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
#define djq 1000000007
const double eps = 1e-10;
const short sint = 0x3f3f;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;
const double alpha = 0.73;
const double PI = acos(-1);
inline void file() {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
}
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int getc() {
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20) + 5, stdin),
                      p1 == p2)
             ? EOF
             : *p1++;
}
inline ll read() {
  rg ll ret = 0, f = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == EOF)
      exit(0);
    if (ch == '-')
      f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    ret = ret * 10 + ch - 48;
    ch = getc();
  }
  return f ? -ret : ret;
}
inline void rdstr(char *s) {
  char ch = getc();
  while (ch < 33 || ch > 126)
    ch = getc();
  while (ch >= 33 && ch <= 126)
    (*s++) = ch, ch = getc();
}
#define ep emplace
#define epb emplace_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define it iterator
#define mkp make_pair
#define naive return 0 * puts("Yes")
#define angry return 0 * puts("No")
#define fls fflush(stdout)
#define rep(i, a) for (rg int i = 1; i <= a; ++i)
#define per(i, a) for (rg int i = a; i; --i)
#define rep0(i, a) for (rg int i = 0; i <= a; ++i)
#define per0(i, a) for (rg int i = a; ~i; --i)
#define szf sizeof
typedef vector<int> vec;
typedef pair<int, int> pii;
struct point {
  int x, y;
  point(int x = 0, int y = 0) : x(x), y(y) {}
  inline bool operator<(const point &T) const {
    return x ^ T.x ? x < T.x : y < T.y;
  };
};
inline int ksm(int base, int p) {
  int ret = 1;
  while (p) {
    if (p & 1)
      ret = 1ll * ret * base % djq;
    base = 1ll * base * base % djq, p >>= 1;
  }
  return ret;
}
inline void pls(int &x, const int k) {
  x = (x + k >= djq ? x + k - djq : x + k);
}
inline int add(const int a, const int b) {
  return a + b >= djq ? a + b - djq : a + b;
}
inline void sub(int &x, const int k) { x = (x - k < 0 ? x - k + djq : x - k); }
inline int inc(const int a, const int b) { return a < b ? a - b + djq : a - b; }
inline void ckmn(int &x, const int k) { x = (k < x ? k : x); }
inline void ckmx(int &x, const int k) { x = (k > x ? k : x); }
const int lim = 2e5;
int fac[200005], ifac[200005];
inline int C(int n, int m) {
  return (m <= n && m >= 0 && n >= 0)
             ? 1ll * fac[n] * ifac[m] % djq * ifac[n - m] % djq
             : 0;
}
void initC() {
  fac[0] = ifac[0] = 1;
  rep(i, lim) fac[i] = 1ll * fac[i - 1] * i % djq;
  ifac[lim] = ksm(fac[lim], djq - 2);
  per(i, lim - 1) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % djq;
}
int n, k, u, v, sz[200005];
vec e[200005];
void dfs(int x, int fa) {
  sz[x] = 1;
  for (int y : e[x])
    if (y ^ fa)
      dfs(y, x), sz[x] += sz[y];
}
signed main() {
  initC();
  n = read(), k = read();
  rep(i, n - 1) u = read(), v = read(), e[u].epb(v), e[v].epb(u);
  dfs(1, 0);
  if (k & 1) // if k is odd, answer is always 1
    return 0 * puts("1");
  else {
    int ans = 0;
    for (rg int i = 2; i <= n; ++i)
      // For each edge connecting to node i, count valid assignments
      pls(ans, 1ll * C(sz[i], k / 2) * C(n - sz[i], k / 2) % djq);
    // Multiply by inverse of total combinations and add 1 for the root
    ans = 1ll * ans * ksm(C(n, k), djq - 2) % djq;
    pls(ans, 1);
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/