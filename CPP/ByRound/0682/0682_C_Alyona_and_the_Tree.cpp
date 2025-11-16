// Problem: CF 682 C - Alyona and the Tree
// https://codeforces.com/contest/682/problem/C

/*
 * Problem: C. Alyona and the Tree
 *
 * Purpose: Given a rooted tree where each vertex has a value 'a[i]' and edges have weights,
 * determine the minimum number of leaves to remove so that no vertex is "sad". A vertex v is sad
 * if there exists a descendant u such that the distance from v to u exceeds a[u].
 *
 * Algorithm: 
 *   - Perform DFS traversal on the tree starting from root (vertex 1)
 *   - For each node, calculate cumulative edge weight from root to current node
 *   - If the path weight exceeds the node's value 'a[u]', then we cannot extend further down
 *   - Count all nodes visited during valid DFS paths, subtract that count from total nodes
 *   - The result is the number of leaves that need to be removed
 *
 * Time Complexity: O(n), where n is the number of vertices. Each vertex and edge is visited once.
 * Space Complexity: O(n), for storing the tree structure and recursion stack in worst case.
 */

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <utility>

void dfs(int64_t node, int64_t dist, const std::vector<int64_t> &a,
         const std::vector<std::vector<std::pair<int64_t, int64_t>>> &tree,
         int64_t &count) {
  // If the accumulated distance exceeds the value of current node, stop extending this branch
  if (dist > a[node])
    return;
  
  // Increment count of valid nodes we can include in our tree
  ++count;
  
  // Traverse all children of current node
  for (int64_t p = 0; p < tree[node].size(); p++) {
    int64_t v = tree[node][p].first;     // Child vertex
    int64_t e = tree[node][p].second;    // Edge weight from parent to child
    
    // Update the accumulated distance with current edge weight
    e += dist;
    
    // Handle negative edge weights (though not needed for correctness in this problem)
    if (e < 0) {
      e = 0;
    }
    
    // Recursively visit child node
    dfs(v, e, a, tree, count);
  }
}

int main() {
  int64_t n;
  scanf("%lld", &n);
  
  // Read the values of all vertices (1-indexed)
  std::vector<int64_t> a(n + 1);
  for (int64_t p = 1; p <= n; p++) {
    scanf("%lld", &a[p]);
  }
  
  // Build adjacency list representation of the tree
  std::vector<std::vector<std::pair<int64_t, int64_t>>> tree(n + 1);
  for (int64_t p = 2; p <= n; p++) {
    int64_t u, x;
    scanf("%lld %lld", &u, &x);
    // Store child vertex and edge weight
    tree[u].push_back(std::make_pair(p, x));
  }
  
  // Counter for valid nodes that can remain in the tree (i.e., not sad)
  int64_t count(0);
  
  // Start DFS from root with initial distance 0
  dfs(1, 0, a, tree, count);
  
  // Final answer: total nodes minus valid nodes gives number of leaves to remove
  printf("%lld\n", (n - count));
  
  return 0;
}


// https://github.com/VaHiX/codeForces/