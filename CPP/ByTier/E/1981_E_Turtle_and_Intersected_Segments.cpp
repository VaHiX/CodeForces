// Problem: CF 1981 E - Turtle and Intersected Segments
// https://codeforces.com/contest/1981/problem/E

/*
 * Problem: Turtle and Intersected Segments
 * 
 * Algorithm: 
 * - Use a sweep line technique with a map to efficiently find intersecting segments.
 * - For each segment, determine which previous segments it intersects with.
 * - Construct a minimum spanning tree (MST) using Kruskal's algorithm on the resulting edges.
 * 
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 * 
 * Key techniques:
 * - Coordinate compression using map for efficient intersection detection
 * - Union-Find (Disjoint Set Union) for MST construction
 * - Sweep line algorithm to reduce the number of intersection checks
 * 
 * Approach:
 * 1. Sort segments by left endpoint
 * 2. Process segments in order, maintaining a map of (a_i, {right_endpoint, index})
 * 3. For each new segment, find intersecting previous segments by checking overlapping intervals
 * 4. Build edges with weights |a_i - a_j| for intersecting segments
 * 5. Apply Kruskal's algorithm to find MST
 * 6. If the graph is not connected, return -1
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
constexpr int maxn = 500001;
tii d[maxn];
int p[maxn];

// Find root of node with path compression
int find(int node) { return node == p[node] ? node : p[node] = find(p[node]); }

void solve() {
  int n, a, b, c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    d[i] = {a, b, c};
  }
  sort(d, d + n); // Sort segments by left endpoint
  iota(p, p + n, 0); // Initialize parent array for Union-Find
  ll ans = 0;
  map<int, pii> mp{{get<2>(d[0]), {get<1>(d[0]), 0}}}; // Map of (a_i, {right_endpoint, index})
  vector<tii> edges; // Store edges: (weight, u, v)
  
  for (int i = 1; i < n; i++) {
    tie(a, b, c) = d[i]; // Current segment (a, b, c)
    
    // Remove segments from map that no longer intersect current segment
    auto p_it = mp.lower_bound(c);
    while (p_it != mp.end() && p_it->second.first < a)
      p_it = mp.erase(p_it);
    
    // Check intersection with segments in the map
    if (p_it != mp.end())
      edges.push_back({p_it->first - c, p_it->second.second, i});
    
    // Check in reverse direction for intersection
    if (p_it != mp.begin()) {
      --p_it;
      while (p_it->second.first < a) {
        p_it = mp.erase(p_it);
        if (p_it != mp.begin())
          p_it = prev(p_it);
        else
          break;
      }
      if (p_it != mp.end() && p_it->first < c)
        edges.push_back({c - p_it->first, p_it->second.second, i});
    }
    
    // Update map with current segment
    if (mp[c].first < b)
      mp[c] = {b, i};
  }
  
  sort(edges.begin(), edges.end()); // Sort edges by weight
  
  int ct = 1; // Count of connected components
  for (auto [c, a, b] : edges) {
    a = find(a), b = find(b); // Find roots
    if (a != b) {
      p[a] = b; // Union
      ct++;
      ans += c; // Add weight to MST
    }
  }
  
  // If all nodes are connected, output sum of weights, otherwise -1
  cout << (ct == n ? ans : -1) << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/