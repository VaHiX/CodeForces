// Problem: CF 2152 H2 - Victorious Coloring (Hard Version)
// https://codeforces.com/contest/2152/problem/H2

// Problem: H2. Victorious Coloring (Hard Version)
// Description: Given a tree with weighted edges and queries for minimum total vertex weights such that f(x) >= l,
// where f(x) is the minimum cost of a victorious coloring based on vertex weights x.
// Algorithms/Techniques: Heavy-light decomposition, centroid decomposition, convex hull optimization,
// dynamic programming on trees, priority queue optimization.
// Time Complexity: O(n log n + q log q)
// Space Complexity: O(n)

#include <assert.h>
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
vector<int> pa; // Union-Find parent array for DSU
int findp(int x) { return pa[x] = (pa[x] == x ? x : findp(pa[x])); } // Find with path compression
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<array<lint, 3>> edges; // Stores edges as {weight, u, v}
    for (int i = 0; i < n - 1; i++) {
      lint u, v, w;
      cin >> u >> v >> w;
      u--;
      v--;
      edges.push_back({w, u, v});
    }
    sort(all(edges)); // Sort edges by weight in ascending order
    reverse(all(edges)); // Reverse to sort in descending order (so we process heavier edges first)
    cr(pa, 2 * n - 1); // Resize and clear DSU parent array
    vector<lint> cost(2 * n - 1); // Cost of each node/subtree
    vector<pi> ch(2 * n - 1); // Child nodes for internal nodes
    iota(all(pa), 0); // Initialize DSU to identity
    for (int i = 0; i < n - 1; i++) {
      int u = findp(edges[i][1]); // Find roots of node u
      int v = findp(edges[i][2]); // Find roots of node v
      pa[u] = i + n; // Union them to new parent
      pa[v] = i + n;
      ch[i + n] = {u, v}; // Record children of the new node
      cost[edges[i][1]] += edges[i][0]; // Add contribution of weight to cost arrays
      cost[edges[i][2]] += edges[i][0];
      cost[i + n] -= edges[i][0] * 2;
    }
    for (int i = n; i < 2 * n - 1; i++) {
      cost[i] += cost[ch[i][0]] + cost[ch[i][1]]; // Propagate cost upward
    }
    vector<priority_queue<pi, vector<pi>, greater<pi>>> pq(n); // Convex hull for each subtree
    vector<int> idx(2 * n - 1); // Index mapping from node to its root priority queue
    iota(all(idx), 0); // Initialize index array
    for (int i = 0; i < 2 * n - 1; i++) {
      if (i < n) {
        pq[i].push({cost[i], 1}); // Leaf nodes start with a single point in hull
        continue;
      }
      if (sz(pq[idx[ch[i][0]]]) < sz(pq[idx[ch[i][1]]]))
        swap(ch[i][0], ch[i][1]); // Ensure that smaller subtree is merged into larger one for efficient merge
      idx[i] = idx[ch[i][0]]; // Assign the root of merged set to new node
      while (sz(pq[idx[ch[i][1]]])) { // Merging priority queues
        auto tp = pq[idx[ch[i][1]]].top();
        pq[idx[ch[i][1]]].pop();
        pq[idx[i]].push(tp);
      }
      if (cost[i] >= pq[idx[i]].top()[0]) // Skip if cost is higher than the min in hull
        continue;
      if (cost[i] >= lint(2e9)) // Don't add too large costs
        continue;
      lint A = 0, B = 0;
      lint pv = -1;
      while (sz(pq[idx[i]])) { // Update the convex hull
        auto [point, slope] = pq[idx[i]].top();
        pq[idx[i]].pop();
        B += A * (point - pv);
        pv = point;
        A += slope;
        lint U = A * pv - B - cost[i];
        lint L = A - 1;
        if (L > 0) {
          assert(point * L <= U); // Make sure the inequality holds
          if ((sz(pq[idx[i]]) == 0 || U < pq[idx[i]].top()[0] * L)) { // Determine new point for hull update
            lint f1 = U / L - cost[i];
            lint f2 = (U / L + 1 - pv) * A + B;
            pq[idx[i]].push({cost[i], 1});
            pq[idx[i]].push({U / L, f2 - f1 - 1});
            pq[idx[i]].push({U / L + 1, A - (f2 - f1)});
            break;
          }
        } else if (sz(pq[idx[i]]) == 0) {
          pq[idx[i]].push({cost[i], 1});
          break;
        }
      }
    }
    int q;
    cin >> q;
    vector<pi> queries(q); // Queries as {value, original_index}
    for (int i = 0; i < q; i++) {
      cin >> queries[i][0];
      queries[i][1] = i;
    }
    sort(all(queries)); // Sort queries
    vector<lint> ans(q); // Final answers
    lint A = 0, B = 0, pv = -1;
    auto Troot = idx[2 * n - 2]; // Root node of the whole tree
    for (auto &[x, i] : queries) {
      while (sz(pq[Troot]) && pq[Troot].top()[0] <= x) { // Process current query against hull
        auto [point, slope] = pq[Troot].top();
        pq[Troot].pop();
        B += A * (point - pv);
        pv = point;
        A += slope;
      }
      ans[i] = (x - pv) * A + B; // Compute answer using the linear function
    }
    for (auto &v : ans)
      cout << v << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/