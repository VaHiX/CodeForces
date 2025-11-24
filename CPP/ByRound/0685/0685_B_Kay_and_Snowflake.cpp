// Problem: CF 685 B - Kay and Snowflake
// https://codeforces.com/contest/685/problem/B

/*
 * Problem: Kay and Snowflake
 * Purpose: Find centroids of subtrees for multiple queries on a tree.
 * Algorithm: 
 *   - Build the tree from parent information
 *   - Use DFS to compute subtree sizes and centroids
 *   - For each node, if the largest child's size is more than half of current subtree,
 *     adjust the centroid by moving up the tree until the condition is satisfied.
 * Time Complexity: O(n + q)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
void dfs(long node, const std::vector<long> &parent,
         const std::vector<std::vector<long>> &h, std::vector<long> &sz,
         std::vector<long> &centroid) {
  sz[node] = 1;                             // Initialize size of subtree rooted at node
  centroid[node] = node;                    // Initially, centroid is the node itself
  long cand(0);                             // Keep track of the largest child subtree
  for (long p = 0; p < h[node].size(); p++) {
    long u = h[node][p];
    dfs(u, parent, h, sz, centroid);        // Recursively process child subtree
    sz[node] += sz[u];                      // Accumulate size of the subtree
    if (cand <= 0 || sz[u] > sz[cand]) {    // Update candidate if current child is larger
      cand = u;
    }
  }
  if (2 * sz[cand] > sz[node]) {            // If largest child is more than half
    long cn = centroid[cand];               // Get centroid of the largest child
    while (sz[node] > 2 * sz[cn]) {         // Move up the tree until valid centroid
      cn = parent[cn];                      // Go to parent
    }
    centroid[node] = cn;                    // Set new centroid for current node
  }
}
int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  std::vector<long> parent(n + 1);
  std::vector<std::vector<long>> h(n + 1);
  for (long p = 2; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    parent[p] = x;                          // Record parent of node p
    h[x].push_back(p);                      // Add p to children list of x
  }
  std::vector<long> centroid(n + 1), sz(n + 1);
  dfs(1, parent, h, sz, centroid);          // Start DFS from root
  for (long p = 0; p < q; p++) {
    long x;
    scanf("%ld", &x);
    printf("%ld\n", centroid[x]);           // Output centroid of subtree rooted at x
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/