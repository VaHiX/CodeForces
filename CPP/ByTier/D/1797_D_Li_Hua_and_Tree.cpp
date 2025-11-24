// Problem: CF 1797 D - Li Hua and Tree
// https://codeforces.com/contest/1797/problem/D

/*
 * Problem: Li Hua and Tree
 * Algorithms/Techniques: DFS, Heavy-Light Decomposition, Set for tracking heavy sons
 * Time Complexity: O(n log n + m log n) where n is number of vertices, m is number of operations
 * Space Complexity: O(n) for storing tree structure, parent info, subtree sizes, sums and sets
 *
 * Key idea:
 * - Use DFS to compute subtree sizes and importance sums
 * - Maintain a set for each node that stores its children sorted by subtree size (descending)
 * - For rotation operation, update parent relationships and subtree sums/sizes appropriately
 * - For query operation, simply return the precomputed sum
 */

#include <math.h>
#include <stddef.h>
#include <algorithm>
#include <bitset>
#include <complex>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#define FI first
#define SE second
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORE(i, a, b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a)                                                          \
  for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define TRAV(x, a) for (auto &x : a)
using namespace std;
using ll = long long;
using ld = double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using cd = complex<ld>;
using vcd = vector<cd>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vs = vector<string>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
template <class T> using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <class T> inline int ckmin(T &a, const T &val) {
  return val < a ? a = val, 1 : 0;
}
template <class T> inline int ckmax(T &a, const T &val) {
  return a < val ? a = val, 1 : 0;
}
template <class T> void remDup(vector<T> &v) {
  sort(ALL(v));
  v.erase(unique(ALL(v)), end(v));
}
constexpr int pct(int x) { return __builtin_popcount(x); }
constexpr int bits(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }
ll ceilDiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
ll floorDiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
void setPrec(int x) { cout << fixed << setprecision(x); }
#define ts to_string
string ts(char c) { return string(1, c); }
string ts(const char *s) { return (string)(s); }
string ts(string s) { return s; }
template <class T> string ts(const T &t) {
  return ts(t);
}
template <class T, class U> string ts(pair<T, U> p) {
  return "(" + ts(p.FI) + ", " + ts(p.SE) + ")";
}
template <size_t i, class T> string print_tuple_utils(const T &tup) {
  if constexpr (i == tuple_size<T>::value)
    return ")";
  else
    return (i ? ", " : "(") + ts(get<i>(tup)) +
           print_tuple_utils<i + 1, T>(tup);
}
template <class... U> string ts(tuple<U...> u) {
  return print_tuple_utils<0, tuple<U...>>(u);
}
template <class T> void pr(T x) { cout << ts(x); }
template <class T, class... U> void pr(const T &t, const U &...u) {
  pr(t);
  pr(u...);
}
void ps() { pr("\n"); }
template <class T, class... U> void ps(const T &t, const U &...u) {
  pr(t);
  if (sizeof...(u))
    pr(" ");
  ps(u...);
}
void DBG() { cerr << "]" << endl; }
template <class T, class... U> void DBG(const T &t, const U &...u) {
  cerr << ts(t);
  if (sizeof...(u))
    cerr << ", ";
  DBG(u...);
}
#ifdef LOCAL_DEBUG
#define CONCAT(x, y) x##y
#define with_level setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#define dbg(...)                                                               \
  cerr << with_level << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__        \
       << "]: [",                                                              \
      DBG(__VA_ARGS__)
#define chk(...)                                                               \
  if (!(__VA_ARGS__))                                                          \
    cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0) << "Line("   \
         << __LINE__ << ") -> function(" << __FUNCTION__                       \
         << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n",               \
        exit(0);
#define db_block() debug_block CONCAT(dbbl, __LINE__)
int __db_level = 0;
struct debug_block {
  debug_block() {
    cerr << with_level << "{" << endl;
    ++__db_level;
  }
  ~debug_block() {
    --__db_level;
    cerr << with_level << "}" << endl;
  }
};
#else
#define dbg(...) 0
#define chk(...) 0
#define db_block() 0
#endif
const ld PI = acos(-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
int n, m, num[MAXN], par[MAXN], imp[MAXN];
ll sum[MAXN];
vi a[MAXN];
set<pi> s[MAXN];

// DFS to compute subtree sizes and sums
void dfs(int u, int p) {
  num[u] = 1;
  sum[u] = imp[u];
  TRAV(v, a[u]) {
    if (v == p)
      continue;
    par[v] = u;
    dfs(v, u);
    num[u] += num[v];
    sum[u] += sum[v];
  }
}

// Handle rotation of heavy child
void handle(int u) {
  if (SZ(s[u]) == 0) {
    return;
  }
  auto V = *s[u].begin(); // Find the heaviest child
  int v = V.second;
  int p = par[u];
  dbg(p, u, v);
  ll sumV = sum[u];
  ll sumU = sum[u] - sum[v];
  sum[v] = sumV;
  sum[u] = sumU;
  int oldNumU = num[u];
  int oldNumV = num[v];
  int numV = num[u];
  int numU = num[u] - num[v];
  num[v] = numV;
  num[u] = numU;
  par[v] = p;
  par[u] = v;
  s[p].erase({-oldNumU, u});
  s[p].insert({-num[v], v});
  s[u].erase({-oldNumV, v});
  s[v].insert({-num[u], u});
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> n >> m;
  FOR(i, 1, n) cin >> imp[i];
  FOR(i, 1, n - 1) {
    int u, v;
    cin >> u >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }
  par[1] = 0;
  dfs(1, 0);
  FOR(u, 1, n) {
    TRAV(v, a[u]) {
      if (v == par[u])
        continue;
      s[u].insert({-num[v], v}); // Insert with negative size for reverse sorting
    }
  }
  while (m--) {
    int u, v;
    cin >> u >> v;
    if (u == 1) {
      cout << sum[v] << "\n";
    } else {
      handle(v);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/