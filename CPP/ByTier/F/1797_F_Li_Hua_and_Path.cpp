// Problem: CF 1797 F - Li Hua and Path
// https://codeforces.com/contest/1797/problem/F

/*
 * Problem: F. Li Hua and Path
 * 
 * Purpose:
 *   This code efficiently calculates the number of "cute pairs" in a dynamic tree
 *   where vertices are added incrementally. A cute pair (u,v) satisfies exactly
 *   one of the two conditions: u is the minimum index on path (u,v), or v is
 *   the maximum index on path (u,v).
 *
 * Algorithm:
 *   - Uses DFS traversal to decompose the tree into a structure suitable for efficient updates.
 *   - Implements a Binary Indexed Tree (Fenwick Tree) for efficient prefix sum queries and updates.
 *   - Maintains a dynamic count of cute pairs using the properties of the tree structure and indices.
 *   - For each new vertex insertion, the number of cute pairs is updated incrementally.
 *
 * Time Complexity:
 *   - Preprocessing: O(n log n)
 *   - Each operation: O(log n)
 *   - Total: O(n log n + m log n)
 *
 * Space Complexity:
 *   - O(n)
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int n, q, x, y, tot, dep[400001], fa[200001], siz[200001], ls[200001],
    rs[200001], t[200001];
long long ans;
vector<int> mx[200001], mn[200001], G[200001];

// Find root of component with path compression
int find(int u) {
  if (fa[u] != u)
    fa[u] = find(fa[u]);
  return fa[u];
}

// Update Fenwick tree at position x with value v
void add(int x, int v) {
  for (int i = x; i <= n; i += i & -i)
    t[i] += v;
}

// Query Fenwick tree up to position x
int ask(int x) {
  int s = 0;
  for (int i = x; i >= 1; i -= i & -i)
    s += t[i];
  return s;
}

// DFS1: Initialize the tree structure and compute initial counts
void dfs1(int x) {
  ls[x] = ++tot, siz[x] = 1;
  for (int y : mx[x])
    dfs1(y), siz[x] += siz[y];
  rs[x] = tot, ans += siz[x] - 1;
}

// DFS2: Process the tree in a manner to calculate the number of cute pairs
void dfs2(int x) {
  ans -= 2 * (ask(rs[x]) - ask(ls[x] - 1)); // Subtract pairs involving current node
  add(ls[x], 1), siz[x] = 1;
  for (int y : mn[x])
    dep[y] = dep[x] + 1, dfs2(y), siz[x] += siz[y];
  add(ls[x], -1), ans += siz[x] - 1; // Add pairs involving current node
}

int main() {
  scanf("%d", &n);
  
  // Build the adjacency list representation of the tree
  for (int i = 2; i <= n; i++) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }

  // Initialize the Union-Find structure for building tree components
  for (int i = 1; i <= n; i++)
    fa[i] = i;
    
  // Build the mx structure: nodes with index greater than their neighbors
  for (int i = 1; i <= n; i++)
    for (int j : G[i])
      if (i > j && find(i) != find(j))
        mx[i].push_back(find(j)), fa[find(j)] = i;

  // Reset Union-Find structure for mn
  for (int i = 1; i <= n; i++)
    fa[i] = i;

  // Build the mn structure: nodes with index smaller than their neighbors
  for (int i = n; i >= 1; i--)
    for (int j : G[i])
      if (i < j && find(i) != find(j))
        mn[i].push_back(find(j)), fa[find(j)] = i;

  // Initialize DFS structures
  dfs1(n);
  dfs2(1);

  // Output initial cute pairs count
  printf("%lld\n", ans);

  // Read number of operations
  scanf("%d", &q);

  // Process each insertion operation
  for (int i = n + 1; i <= n + q; i++) {
    scanf("%d", &x);
    dep[i] = dep[x] + 1;
    // Update the answer by adding the new contributions
    printf("%lld\n", ans += i - 1 - dep[i]);
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/