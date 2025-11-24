// Problem: CF 1454 E - Number of Simple Paths
// https://codeforces.com/contest/1454/problem/E

/*
E. Number of Simple Paths
Algorithms/Techniques: Tree decomposition using BFS, centroid-like approach, graph traversal, combinatorics

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This code computes the number of simple undirected paths in a connected graph with n vertices and n edges.
The key insight is that such a graph contains exactly one cycle. The algorithm removes leaves iteratively,
building up component sizes, then uses combinatorics to count all possible paths:
For each component with 'dep[p]' nodes, we compute:
- Paths within the component: dep[p] * (dep[p] - 1) / 2
- Paths connecting to other components: dep[p] * (n - dep[p])
The result is the sum over all components.
*/
#include <cstdio>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::set<ll>> g(n + 1); // adjacency list using sets for fast insertion/deletion
    for (ll p = 0; p < n; p++) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      g[x].insert(y);  // build adjacency set
      g[y].insert(x);
    }
    std::queue<ll> q;  // queue for BFS processing leaves
    for (ll p = 1; p <= n; p++) {
      if (g[p].size() == 1) {  // if node is a leaf
        q.push(p);
      }
    }
    std::vector<ll> dep(n + 1, 1);  // component size initialization, each node starts with size 1
    while (q.size()) {
      ll x = q.front();  // process current leaf
      q.pop();
      ll y = *g[x].begin();  // get neighbor of leaf
      dep[y] += dep[x];  // accumulate component size into neighbor
      dep[x] = 0;  // mark processed node as 0
      g[x].erase(y);  // remove edge from both ends
      g[y].erase(x);
      if (g[y].size() == 1) {  // if new leaf, add to queue
        q.push(y);
      }
    }
    ll ans(0);
    for (ll p = 1; p <= n; p++) {
      ans += dep[p] * (dep[p] - 1) / 2 + dep[p] * (n - dep[p]);  // total paths contributed by this component
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/