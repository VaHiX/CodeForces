// Problem: CF 1676 G - White-Black Balanced Subtrees
// https://codeforces.com/contest/1676/problem/G

/*
G. White-Black Balanced Subtrees

Algorithm:
The solution uses a depth-first search (DFS) traversal of the tree to compute for each subtree:
- The balance score (number of white minus number of black vertices)
- Count of subtrees that are balanced (i.e., balance score is zero)

Time Complexity: O(n) per test case, as each node is visited once in DFS.
Space Complexity: O(n) for storing the tree structure and recursion stack.

Techniques:
- Tree representation using adjacency list
- DFS post-order traversal to accumulate subtree information
- Balance tracking via a signed count (positive for white, negative for black)
*/

#include <iostream>
#include <vector>
#include <string>

long dfs(long node, const std::vector<std::vector<long>> &g,
         const std::string &s, long &cnt) {
  // Calculate balance for current node: +1 for 'W', -1 for 'B'
  long total = (s[node] == 'W') - (s[node] == 'B');
  for (long p = 0; p < g[node].size(); p++) {
    long x = g[node][p];
    // Recursively process children and accumulate their balance
    total += dfs(x, g, s, cnt);
  }
  // If total balance is zero, this subtree is balanced
  cnt += (!total);
  return total;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::vector<long>> g(n + 1); // Tree adjacency list
    for (long p = 2; p <= n; p++) {
      long x;
      std::cin >> x;
      g[x].push_back(p); // Build tree from parent to children
    }
    std::string s;
    std::cin >> s;
    s = '_' + s; // Make indexing 1-based
    long cnt(0);
    dfs(1, g, s, cnt); // Start DFS from root
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/