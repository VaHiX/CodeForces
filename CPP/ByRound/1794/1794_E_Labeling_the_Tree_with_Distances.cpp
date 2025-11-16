// Problem: CF 1794 E - Labeling the Tree with Distances
// https://codeforces.com/contest/1794/problem/E

/*
Purpose: This code finds all "good" vertices in a tree based on a given list of integers.
         A vertex x is good if there exists a way to assign the integers from the list to the 
         other vertices such that the label of each vertex i equals the distance from x to i.
         The solution uses tree DFS traversal and hashing techniques to efficiently determine
         valid assignments.

Algorithms/Techniques:
- Tree DFS traversal for computing subtree sizes and distances
- Hashing to compare subtree structures against possible labelings
- Preprocessing of the given array a[] to generate hash values
- Backtracking through the tree in a second DFS to check if a vertex can serve as a good root

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <complex>
#include <utility>
#include <vector>

using namespace std;
#define mem(a) memset(a, 0, sizeof(a))
#define INF (~(1 << 31))
#define inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
#define PI 3.141592653589793238462643383
#define lowbit(x) ((x) & (-x))
#define sqr(x) ((x) * (x))
#define pb(x) emplace_back(x)
#define pf(x) push_front(x)
#define all(v) (v).begin(), (v).end()
#define dbg(x, y) cout << (x) << " = " << (y) << endl;
#define per(i, a, b) for (int i = a; i >= b; --i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define fi first
#define se second
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define ll long long
#define int ll
#define __int128 int
typedef bitset<2010> bt;
typedef unsigned long long ull;
typedef complex<double> comp;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
const ll N = 2e5 + 7;
const ll M = 1e9 + 7;
const ll MAXN = 4e18 + 7;
const ll Mod = 998244353;
int _, i, j, k, n, m, p, s, T, t, l, r, o, u, v, w, x, y, z, ans, sum, num, len,
    en, sx, sy, tx, ty, th, ma, mi, mod, cnt, la, op, res, flag, cas, bk, ret,
    mid, now, tmp, rt;
int a[N], b[N], c[N], d[N];
char ch;
vector<int> h, g[N], I;
char s1[N], s2[N], s3, s4;
int base = 23333, wet[N], sub[N], inc;
void dfs(int u, int fa) {
  c[u] = 1;
  d[u] = 0;
  sub[u] = 1;
  for (auto v : g[u]) {
    if (v == fa)
      continue;
    dfs(v, u);
    c[u] += c[v];
    d[u] += c[v] + d[v];
    sub[u] = (sub[u] + base * sub[v]) % M;
  }
}
void ser(int u, int fa, int sum, int hs) {
  int la = sum - s; // Computes the leftover sum to check against our list
  if (la < n && la >= 0 && (hs % M + M) % M == (inc + wet[la]) % M)
    h.pb(u); // If valid match, add vertex u to results
  for (auto v : g[u]) {
    if (v == fa)
      continue;
    ser(v, u, sum - c[v] + (n - c[v]),
        ((hs - sub[v] * base % M) * base + sub[v]) % M); // Recurse with updated structure hash
  }
}
signed main() {
  int T = 1;
  while (T--) {
    scanf("%lld", &n);
    wet[0] = 1;
    for (i = 1; i <= n; ++i)
      wet[i] = wet[i - 1] * base % M; // Precompute powers of base for hashing
    s = 0;
    inc = 0;
    for (i = 1; i < n; ++i)
      scanf("%lld", a + i), s += a[i], inc += wet[a[i]]; // Sum and hashing of given array
    for (i = 1; i < n; ++i) {
      scanf("%lld%lld", &u, &v);
      g[u].pb(v);
      g[v].pb(u);
    }
    dfs(1, 0); // First DFS to compute necessary values
    ser(1, 0, d[1], sub[1]); // Second DFS to find good vertices
    sort(all(h));
    printf("%lld\n", (int)h.size());
    for (auto v : h)
      printf("%lld ", v);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/