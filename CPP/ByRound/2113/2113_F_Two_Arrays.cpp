// Problem: CF 2113 F - Two Arrays
// https://codeforces.com/contest/2113/problem/F

/*
F. Two Arrays
Algorithms/Techniques: Graph traversal (DFS), greedy approach, edge manipulation.

Time Complexity: O(n) amortized per test case due to union-find like processing of edges.
Space Complexity: O(n) for storing arrays and graph structure.

The problem asks to maximize the sum of distinct elements in two arrays by swapping
elements at same indices. The solution builds a graph where each node represents a number,
and directed edges represent possible swaps between two numbers from different arrays.
Using DFS traversal, we process components of the graph and try to minimize duplicates
to increase distinct counts in both arrays.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>

using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for (auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for (auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx), end(Tx)
const int N = 2e5 + 5;
int n, a[N], b[N];
int h[N], e[N * 2], ne[N * 2], w[N * 2], idx; // Graph representation for adjacency list
int cnt[N], cnt1[N]; // Count occurrences of values in arrays a and b
bool vis[N], vis1[N]; // Visited flags to avoid reprocessing

void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; // Add edge to adjacency list
}

void dfs1(int x, int color, bool f) {
  if (vis[x])
    return;
  vis[x] = 1; // Mark current node as visited
  for (int i = h[x]; ~i; i = ne[i]) { // Traverse all adjacent edges
    int j = e[i];
    if (vis1[abs(w[i])]) // If edge already processed, skip
      continue;
    vis1[abs(w[i])] = 1; // Mark edge as visited
    
    // Apply swap if necessary based on current edge weight sign and color
    if (color == 0 && w[i] > 0)
      swap(a[w[i]], b[w[i]]);
    if (color == 1 && w[i] < 0)
      swap(a[abs(w[i])], b[abs(w[i])]);
    
    dfs1(j, color, 0); // Recurse on neighbor node
    
    if (f) // For handling components with degree >= 2
      color = 1 - color; // Toggle color for alternating strategy
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  
  while (T--) {
    cin >> n;
    
    // Reset graph and counters
    For(i, 0, 2 * n + 2) h[i] = -1;
    For(i, 0, 2 * n + 2) vis[i] = vis1[i] = cnt[i] = 0;
    idx = 0;
    
    // Read input arrays
    For(i, 1, n) cin >> a[i];
    For(i, 1, n) cin >> b[i];
    
    // Count frequency of each element in both arrays
    For(i, 1, n) cnt[a[i]]++, cnt[b[i]]++;
    
    // Build the graph: connect a[i] to b[i] with edge index i, and reverse connection with -i
    For(i, 1, n) add(a[i], b[i], i);  
    For(i, 1, n) add(b[i], a[i], -i);
    
    // Compute initial distinct count
    int ans = 0;
    For(i, 1, 2 * n) 
      ans += (cnt[i] >= 1) + (cnt[i] >= 2);
    
    cout << ans << '\n';
    
    // Handle nodes with single count and higher
    For(i, 1, 2 * n) if (cnt[i] == 1 && !vis[i]) dfs1(i, 1, 0); // One occurrence, no toggle
    For(i, 1, 2 * n) if (cnt[i] >= 2 && !vis[i]) dfs1(i, 1, 1); // Multiple occurrences, toggle possible
    
    For(i, 1, n) cout << a[i] << ' ';
    cout << '\n';
    For(i, 1, n) cout << b[i] << ' ';
    cout << '\n';
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/