// Problem: CF 1806 E - Tree Master
// https://codeforces.com/contest/1806/problem/E

/*
Code Purpose:
This code solves the Tree Master problem where we have a rooted tree with weighted vertices,
and for each query involving two vertices of the same depth, we compute a specific sum
of products along their paths to the root.

The algorithm uses a recursive approach with memoization to efficiently calculate f(x, y),
which sums the products of weights along the paths from vertices x and y to the root.

Algorithms/Techniques:
- Tree traversal using BFS for depth calculation
- Recursive function with memoization for query processing
- Depth-based optimization with modular arithmetic

Time Complexity: O(n + q * D) where D is maximum depth, and n, q are number of nodes and queries
Space Complexity: O(n + q) for storing tree structure, depths, and memoization cache
*/
#include <stdlib.h>
#include <algorithm>
#include <complex>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
using namespace std;
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define each(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert
template <class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
const ll p = 998244353;
const char nl = '\n';
const int MX = 987654321;
const int K = 110;
ll f(ll x, ll y, unordered_map<ll, ll> &m, vl &a, vl &p, vl &d, ll n, ll seed) {
  if (x < y) {
    swap(x, y); // Ensure x is deeper or equal to y to simplify processing
  }
  ll ans = 0;
  ll depth = d[x] % K; // Use modular arithmetic to optimize depth handling
  if (depth == 0)
    depth = K;
  while (x != -1) {
    ans += a[x] * a[y]; // Accumulate product of weights along current path
    x = p[x]; // Move to parent of x
    y = p[y]; // Move to parent of y
    depth--;
    if (!depth) // Break early if depth reaches zero to limit iterations
      break;
  }
  if (x == -1) // If we reached root for x, return computed answer
    return ans;
  if (m.find(n * x + y + seed) != m.end()) { // Check if value already computed
    return m[n * x + y + seed] + ans; // Return cached result plus current partial answer
  }
  return (m[n * x + y + seed] = f(x, y, m, a, p, d, n, seed)) + ans; // Compute and cache new result
}
void solve() {
  int n, q;
  cin >> n >> q;
  vl a(n);
  vl p(n, -1); // Parent array initialized with -1
  vector<vl> edge(n, vl()); // Adjacency list for tree
  F0R(i, n) cin >> a[i]; // Read weights
  FOR(i, 1, n) {
    cin >> p[i], --p[i]; // Read parent information and adjust to 0-indexed
    edge[p[i]].pb(i);
    edge[i].pb(p[i]); // Build adjacency list for BFS traversal
  }
  vl d(n, -1); // Depth array initialized with -1
  queue<pl> qu;
  qu.push({0, 0}); // Start BFS from root (0)
  while (!qu.empty()) {
    pl x = qu.front();
    qu.pop();
    if (d[x.f] >= 0) // Skip already visited nodes
      continue;
    d[x.f] = x.s; // Record depth
    each(y, edge[x.f]) { qu.push({y, x.s + 1}); } // Add children to queue
  }
  unordered_map<ll, ll> m; // Memoization hash map
  ll seed = rand(); // Random seed for hashing
  F0R(i, q) {
    ll x, y;
    cin >> x >> y;
    x--, y--; // Convert to 0-indexed
    cout << f(x, y, m, a, p, d, n, seed) << nl; // Process query
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/