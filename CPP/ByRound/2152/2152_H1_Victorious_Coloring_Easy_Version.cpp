// Problem: CF 2152 H1 - Victorious Coloring (Easy Version)
// https://codeforces.com/contest/2152/problem/H1

/*
 * Problem: Victorious Coloring (Easy Version)
 * Algorithms/Techniques: Union-Find, DFS, Greedy, Tree Decomposition
 *
 * Time Complexity: O(n log n + q * n) where n is the number of vertices and q is the number of queries.
 * Space Complexity: O(n) for storing the tree structure and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
template <typename T> void chmin(T &x, T y) { x = min(x, y); }
template <typename T> void chmax(T &x, T y) { x = max(x, y); }
constexpr int N = 2.5e5;
int T, n, m;
struct Eg {
  int u, v, w;
} e[N + 5];
int fa[2 * N + 5]; // Union-Find parent array
int getfa(int x) {
  if (fa[x] == x)
    return x;
  return fa[x] = getfa(fa[x]); // Path compression
}
vector<int> E[2 * N + 5]; // Adjacency list for the MST tree
ll sum[2 * N + 5]; // Sum of weights in subtree rooted at node
void dfs(int x) {
  for (int v : E[x]) {
    dfs(v); // Traverse children first
    sum[x] += sum[v]; // Accumulate sum from children
  }
}
int q, l;
ll ans[2 * N + 5]; // Result for each query
void solve(int x) {
  ans[x] = 0; // Initialize answer for current node
  for (int v : E[x]) {
    solve(v); // Recursively solve for children
    ans[x] += ans[v]; // Add answers from children
  }
  chmax(ans[x], l - sum[x]); // Update with constraint from query
}
void clear(vector<int> &vec) {
  vector<int> tmp;
  swap(tmp, vec); // Clear vector using swap trick
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), m = n; // Initialize m
    iota(fa + 1, fa + 2 * n, 1); // Initialize Union-Find array with values 1..2*n
    fill(sum, sum + 2 * n, 0); // Reset sum array
    fr(i, 1, 2 * n - 1) clear(E[i]); // Clear adjacency list
    fr(i, 2, n) { // Read edges and store in e array
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      e[i - 1] = {u, v, w};
    }
    sort(e + 1, e + n, [](Eg x, Eg y) { return x.w > y.w; }); // Sort edges descending by weight
    fr(i, 1, n - 1) {
      int u = e[i].u, v = e[i].v, w = e[i].w;
      sum[u] += w, sum[v] += w; // Add edge weights to nodes
      u = getfa(u), v = getfa(v); // Find roots of components
      fa[u] = fa[v] = ++m; // Merge components into new node (increment m)
      E[m].pb(u); // Build tree structure using adjacency list
      E[m].pb(v);
      sum[m] -= 2 * w; // Adjust total weight
    }
    dfs(m); // Perform DFS to compute subtree sums
    scanf("%d", &q); // Read number of queries
    while (q--) {
      scanf("%d", &l); // Read query l
      solve(m); // Process the tree for current query
      printf("%lld\n", ans[m]); // Print result for this query
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/