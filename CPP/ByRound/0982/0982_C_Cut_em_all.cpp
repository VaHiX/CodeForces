// Problem: CF 982 C - Cut 'em all!
// https://codeforces.com/contest/982/problem/C

/*
 * Problem: Cut 'em all!
 * 
 * Purpose: Given a tree with n vertices, determine the maximum number of edges 
 *          that can be removed such that all remaining connected components have even size.
 * 
 * Algorithm: 
 * - Perform a DFS traversal of the tree starting from any node (say node 1).
 * - For each subtree rooted at a node, compute the size of the subtree.
 * - If a subtree has an even number of nodes, we can cut the edge connecting it to its parent.
 * - The total number of such edges gives the answer.
 * 
 * Key Insight:
 * - A tree with n nodes can only be split into components of even size if n itself is even.
 *   So if n is odd, return -1.
 * 
 * Time Complexity: O(n) - Each node and edge is visited once during DFS.
 * Space Complexity: O(n) - For the adjacency list representation of the tree and recursion stack.
 */

#include <cstdio>
#include <vector>

// DFS function to traverse the tree and count removable edges
// 'g' is the adjacency list of the tree
// 'node' is the current node being processed
// 'from' is the parent node to avoid going back
// 'cnt' keeps track of the number of removable edges
long dfs(const std::vector<std::vector<long>> &g, long node, long from,
         long &cnt) {
  long below(1);  // Initialize the size of the current subtree with 1 (the node itself)
  for (long p = 0; p < g[node].size(); p++) {
    long cur = g[node][p];
    if (cur == from) {
      continue;  // Skip the parent to avoid revisiting
    }
    long u = dfs(g, cur, node, cnt);  // Recursively process the child subtree
    if (u % 2 == 0) {  // If the subtree size is even, we can cut this edge
      ++cnt;
    }
    below += u;  // Add the size of the child subtree to the total size below
  }
  return below;  // Return the total size of the subtree rooted at node
}

int main() {
  long n;
  scanf("%ld", &n);
  
  // If the number of nodes is odd, it's impossible to split the tree into all even-sized components
  if (n % 2) {
    puts("-1");
    return 0;
  }
  
  // Create adjacency list representation of the tree
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);  // Add edge x-y
    g[y].push_back(x);  // Add edge y-x (since the tree is undirected)
  }
  
  long cnt(0);  // Initialize the counter for removable edges
  dfs(g, 1, 0, cnt);  // Start DFS from root node 1
  printf("%ld\n", cnt);  // Print the maximum number of removable edges
  return 0;
}


// https://github.com/VaHiX/CodeForces/