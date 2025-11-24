// Problem: CF 1795 F - Blocking Chips
// https://codeforces.com/contest/1795/problem/F

/*
Algorithm: Binary search on the answer with DFS and greedy validation
Approach:
1. Build the tree and perform DFS to calculate depths
2. For a given number of moves 'x', distribute the moves among the chips greedily
3. Use a greedy validation function to check if it's possible to perform 'x' moves
4. Binary search on the answer to find maximum possible moves

Time Complexity: O(n * log(n)) per testcase where n is number of vertices
Space Complexity: O(n) for storing tree and auxiliary arrays
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
#define clr(x) vector<int>().swap(x);
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound
#define endl '\n'
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vvi vector<vector<int>>
#define vii vector<pii>
#define random                                                                 \
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());      \
  mt19937 rnd(time(0));
#define FAST                                                                   \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define F first
#define S second
#define le v * 2
#define re v * 2 + 1
#define tm (tl + tr) / 2
#define no                                                                     \
  {                                                                            \
    cout << "NO" << endl;                                                      \
    return;                                                                    \
  }
#define yes                                                                    \
  {                                                                            \
    cout << "YES" << endl;                                                     \
    return;                                                                    \
  }
#define getunique(v)                                                           \
  {                                                                            \
    sort(v.begin(), v.end());                                                  \
    v.erase(unique(v.begin(), v.end()), v.end());                              \
  }
const ll INF = 9e18;
const ll MN = -2e9;
const ll MX = 2e5 + 9;
const ll MXX = 2e9;
const ll SQ = 6e2;
const ll MOD = 1e9 + 7;
const ll PP = 1e6 + 3;
const ll P2 = 1299827;
const ld PI = 3.141592653589793;
const ld eps = 1e-11;
template <class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
typedef tree<ll, null_type, greater_equal<ll>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
int n, k;
int a[MX], b[MX];
int p[MX], d[MX], dist[MX];
int Free[MX], take[MX];
vector<int> order, adj[MX];
void init() {
  order.clear();
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    b[i] = 0;
  }
}
void dfs(int u, int par) {
  p[u] = par;
  dist[u] = dist[par] + 1;
  for (auto v : adj[u])
    if (v != par) {
      dfs(v, u);
    }
}
bool up(int u) {
  if (b[u] && take[u] >= 0)
    return false;
  if (b[u]) {
    take[u] = d[u];
  }
  if (take[u] >= 0 && take[u] <= Free[u])
    return true;
  if (take[u] >= 0) {
    Free[u] = -1;
  }
  int pr = p[u];
  if (take[pr] >= 0 && take[u] >= 0)
    return false;
  take[pr] = max(take[pr], take[u] - 1);
  Free[pr] = max(Free[pr], Free[u] + 1);
  return true;
}
bool ok(int x) {
  for (int i = 1; i <= n; i++) {
    d[i] = 0;
    Free[i] = 0;
    take[i] = -1;
  }
  int r = x % k;
  for (int i = 0; i < k; i++) {
    d[a[i]] = x / k + (i < r);
  }
  take[0] = 1;
  for (auto u : order) {
    if (!up(u)) {
      return false;
    }
  }
  return true;
}
void solve() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> a[i];
    b[a[i]] = 1;
  }
  for (int i = 1; i <= n; i++) {
    order.pb(i);
  }
  dfs(1, 0);
  sort(all(order), [&](int &i, int &j) { return dist[i] > dist[j]; });
  int lo = 0, hi = n, mid = 0;
  while (lo < hi) {
    mid = (lo + hi + 1) / 2;
    if (ok(mid))
      lo = mid;
    else
      hi = mid - 1;
  }
  cout << hi << endl;
  init();
}
int main() {
  FAST;
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/