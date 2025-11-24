// Problem: CF 2155 F - Juan's Colorful Tree
// https://codeforces.com/contest/2155/problem/F

/*
F. Juan's Colorful Tree

This code solves the problem of finding the intersection of color sets along paths in a tree.
The approach uses DFS traversal to assign unique identifiers to color occurrences and then
uses a technique to efficiently answer queries about color intersections on paths.

Algorithms/Techniques:
- Tree DFS with path tracking
- Two-pointer technique for intersection counting
- Bucket optimization for large color sets (> B = 700)

Time Complexity: O(n * k + q * sqrt(k))
Space Complexity: O(n * k + q * sqrt(k))

Where n is number of nodes, k is number of colors, and q is number of queries.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define fastIO                                                                 \
  cin.tie(0)->sync_with_stdio(0);                                              \
  cin.exceptions(cin.failbit);
using ll = int;
using vll = vector<ll>;
const ll MAXN = 3e5 + 5, B = 700;
vll g[MAXN], novel[MAXN], comp[MAXN];
ll cur[MAXN], lst[MAXN], to[MAXN], ans[MAXN / B + 10][MAXN];
bool vis[MAXN];
ll t, id;

void dfs(ll v, ll p) {
  // Precompute suffix arrays and assign unique IDs to each color in node v
  vll sf1(novel[v].size()), sf2(novel[v].size());
  comp[v].resize(novel[v].size());
  for (int i = 0; i < (ll)novel[v].size(); i++) {
    ll n = novel[v][i];
    sf1[i] = lst[n];       // Save previous value of lst[n]
    sf2[i] = cur[n];       // Save previous value of cur[n]
    cur[n] = (lst[n] == p ? cur[n] : t++);  // Assign new ID if not from parent
    comp[v][i] = cur[n];   // Store the assigned ID in component
    lst[n] = v;            // Update lst to current node
  }
  // Recursively visit children
  for (auto u : g[v])
    if (u != p)
      dfs(u, v);
  // Restore original values after DFS
  for (int i = 0; i < (ll)novel[v].size(); i++) {
    ll n = novel[v][i];
    lst[n] = sf1[i];
    cur[n] = sf2[i];
  }
}

void solve() {
  ll n, k, s, q, a, b;
  t = 0;
  id = 0;
  cin >> n >> k >> s >> q;
  
  // Reset data structures
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    novel[i].clear();
    comp[i].clear();
    vis[i] = false;
  }
  for (int i = 0; i <= k; i++)
    cur[i] = -1, lst[i] = -1;
    
  // Read edges
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  
  // Read color assignments to nodes
  for (int i = 0; i < s; i++) {
    cin >> a >> b;
    novel[a].push_back(b);
  }
  
  // DFS traversal to assign IDs
  dfs(1, 0);
  
  // Sort components by ID for efficient binary search later
  for (int i = 1; i <= n; i++)
    sort(comp[i].begin(), comp[i].end());
  
  // Process large component sets using precomputed bucket arrays
  for (int i = 1; i <= n; i++) {
    if (novel[i].size() < B)
      continue;
    // Mark all IDs in this component
    for (auto x : comp[i])
      vis[x] = true;
      
    // Count intersections of current large set with all others
    for (int v = 1; v <= n; v++) {
      ans[id][v] = 0;
      for (auto x : comp[v])
        ans[id][v] += vis[x];  // Add to count if present in large set
    }
    
    // Unmark IDs for next iteration
    for (auto x : comp[i])
      vis[x] = false;
      
    to[i] = id++;  // Store which bucket corresponds to this node
  }
  
  // Process queries
  for (int i = 0; i < q; i++) {
    cin >> a >> b;
    if (novel[a].size() < novel[b].size())
      swap(a, b);  // Ensure a is the larger set to avoid overflow
      
    // If a's component is large, use precomputed bucket result
    if (novel[a].size() >= B) {
      cout << ans[to[a]][b] << " ";
      continue;
    }
    
    // Otherwise, use two pointer technique to count intersection
    ll pos1 = 0, pos2 = 0, res = 0;
    while (pos1 < (ll)comp[a].size() && pos2 < (ll)comp[b].size()) {
      if (comp[a][pos1] < comp[b][pos2])
        pos1++;
      else if (comp[a][pos1] > comp[b][pos2])
        pos2++;
      else
        res++, pos1++, pos2++;  // If equal, increment intersection count and both pointers
    }
    cout << res << " ";
  }
}

int main() {
  fastIO;
  ll tt;
  cin >> tt;
  while (tt--) {
    solve();
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/