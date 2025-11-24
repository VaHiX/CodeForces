// Problem: CF 1827 D - Two Centroids
// https://codeforces.com/contest/1827/problem/D

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <random>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T> using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
clock_t startTime;
double getCurrentTime() {
  return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
template <typename T> struct Fenwick {
  vector<T> a;
  int n;
  Fenwick() : a(), n(0) {}
  Fenwick(int _n) {
    n = _n;
    a = vector<T>(n, T());
  }
  void clear() { a = vector<T>(n, T()); }
  void add(int p, T x) {
    for (; p < n; p |= p + 1)
      a[p] += x;
  }
  T get(int r) {
    if (r < 0)
      return T();
    r = min(r, n - 1);
    T res = T();
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res += a[r];
    return res;
  }
  T getSum(int l, int r) { return get(r - 1) - get(l - 1); }
};
const int N = 500500;
int n;
int par[N];
int t[N][2];
int T;
vector<pii> g[N];
void dfs(int v) {
  t[v][0] = T++;
  for (pii &e : g[v]) {
    dfs(e.second);
    e.first = t[e.second][0];
  }
  t[v][1] = T;
}
bool isAnc(int v, int u) { return t[v][0] <= t[u][0] && t[u][1] <= t[v][1]; }
int getSon(int v, int u) {
  assert(isAnc(v, u));
  assert(v != u);
  int p = lower_bound(all(g[v]), mp(t[u][0] + 1, -1)) - g[v].begin();
  assert(p > 0);
  p--;
  v = g[v][p].second;
  assert(isAnc(v, u));
  return v;
}
void solve() {
  scanf("%d", &n);
  par[0] = -1;
  for (int i = 0; i < n; i++)
    g[i].clear();
  for (int i = 1; i < n; i++) {
    scanf("%d", &par[i]);
    par[i]--;
    g[par[i]].push_back(mp(-1, i));
  }
  T = 0;
  dfs(0);
  Fenwick<int> fenv = Fenwick<int>(n);
  fenv.add(t[0][0], 1);
  fenv.add(t[1][0], 1);
  int v = 0, u = 1;
  int sv = 2, su = 1;
  printf("0");
  for (int i = 2; i < n; i++) {
    // Update subtree sizes when adding new node i
    if (isAnc(v, i))
      sv++;
    if (isAnc(u, i))
      su++;
    fenv.add(t[i][0], 1);
    // Check if v is still a centroid, update if not
    if (2 * sv < i + 1) {
      u = v;
      su = sv;
      v = par[v];
      sv = fenv.getSum(t[v][0], t[v][1]);
      assert(2 * sv >= i + 1);
    }
    // Check if i can be a centroid and try to improve centroid pair
    if (isAnc(v, i)) {
      int w = getSon(v, i);
      int x = fenv.getSum(t[w][0], t[w][1]);
      if (2 * x >= i + 1) {
        // w becomes new centroid v
        v = w;
        sv = x;
        assert(v != i);
        u = getSon(v, i);
        su = fenv.getSum(t[u][0], t[u][1]);
      } else if (x > su) {
        // Update u to w if it gives a better solution
        u = w;
        su = x;
      }
    }
    // Compute minimal operations needed to get two centroids
    printf(" %d", min(2 * sv - (i + 1), (i + 1) - 2 * su));
  }
  printf("\n");
}
int main() {
  startTime = clock();
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    solve();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/