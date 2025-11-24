// Problem: CF 2021 E3 - Digital Village (Extreme Version)
// https://codeforces.com/contest/2021/problem/E3

/*
E3. Digital Village (Extreme Version)

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression and union by size
- Sorting edges in ascending order of weight to build MST progressively
- Greedy approach: For each number of servers k, we greedily assign the smallest possible latencies
- Dynamic assignment of servers using a bag of "unused" costs when merging clusters

Time Complexity:
O(m log m + n * α(n) + n log n), where α(n) is the inverse Ackermann function.
Sorting edges takes O(m log m), Union-Find operations take nearly constant time, and final sorting of bag costs takes O(n log n).

Space Complexity:
O(n + m), for storing parent, size, and edge information.

*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define maxn 200'007
int par[maxn];      // Parent array for Union-Find
int sz[maxn];       // Size of each component in Union-Find
long long cal[maxn]; // Total cost accumulated for each component
pair<long long, pair<int, int>> edges[maxn]; // Edges stored as (weight, (u, v))
int find(int u) { return par[u] == u ? u : par[u] = find(par[u]); } // Find with path compression
vector<long long> bag; // Stores unused edge weights for calculating total latency
long long answer[maxn], total;
int cur;

// Unite two components and update cost accordingly
void unite(int u, int v, long long w) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  // Calculate savings from merging: how much we save by connecting smaller to larger
  long long valu = w * sz[u] - cal[u], valv = w * sz[v] - cal[v];
  if (valu < valv) {
    swap(u, v);
    swap(valu, valv);
  }
  // If both are non-empty, store the savings cost in bag
  if (sz[u] && sz[v]) {
    bag.push_back(valv);
  }
  // Merge smaller component into larger one
  sz[u] += sz[v];
  cal[u] += w * sz[v];
  par[v] = u;
}

void solve() {
  int n, m, k; // n: houses, m: cables, p: houses needing internet (k is given as p)
  cin >> n >> m >> k; // k = number of houses requiring internet (p in problem statement)
  cur = k - 1; // Index to track current answer
  total = 0;
  bag.clear();
  for (int i = 1; i <= n; i++) {
    sz[i] = 0;
    par[i] = i;
    cal[i] = 0;
    answer[i] = 0;
  }
  // Mark which houses require internet
  for (int i = 1; i <= k; i++) {
    int input;
    cin >> input;
    sz[input]++;
  }
  // Read all edges
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[i] = {w, {u, v}};
  }
  // Sort edges in ascending weight order to build MST
  sort(edges + 1, edges + 1 + m);
  // Process each edge to merge components
  for (int i = 1; i <= m; i++)
    unite(edges[i].second.first, edges[i].second.second, edges[i].first);
  
  // Sort the saved costs in ascending order for optimal greedy filling
  sort(bag.begin(), bag.end());
  // Calculate answer for each k from n down to 1 by accumulating savings
  for (auto &x : bag) {
    total += x;
    answer[cur--] = total;
  }
  // Print answers
  for (int i = 1; i <= n; i++)
    cout << answer[i] << ' ';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/