// Problem: CF 767 C - Garland
// https://codeforces.com/contest/767/problem/C

/*
Purpose: This program solves the problem of cutting two wires from a garland (tree structure) such that the three resulting parts have equal sum of temperatures.
Algorithms/Techniques: Depth-First Search (DFS) on a tree to compute subtree sums and identify cut points.
Time Complexity: O(n), where n is the number of lamps, as each node is visited once during DFS.
Space Complexity: O(n), for storing the tree structure and recursion stack in worst case (a long chain).
*/

#include <cstdio>
#include <vector>
long dfs(long node, long target, const std::vector<std::vector<long>> &h,
         const std::vector<long> &t, std::vector<long> &cuts) {
  if (cuts.size() >= 2) {
    return 0;
  }
  long subsum = t[node];  // Start with current node's temperature
  for (long p = 0; p < h[node].size(); p++) {
    long u = h[node][p];
    subsum += dfs(u, target, h, t, cuts);  // Recursively process children
  }
  if (cuts.size() >= 2) {
    return 0;
  } else if (subsum == target) {
    cuts.push_back(node);  // If subtree sum equals target, record this node as a cut point
    return 0;
  }
  return subsum;  // Return the sum of subtree rooted at node
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> t(n);
  std::vector<std::vector<long>> h(n);  // h[i] contains list of children of node i
  long root(-1), tsum(0);
  for (long p = 0; p < n; p++) {
    long par, temp;
    scanf("%ld %ld", &par, &temp);
    t[p] = temp;
    tsum += temp;
    if (par == 0) {
      root = p;  // Find the root (node with parent 0)
    } else {
      h[par - 1].push_back(p);  // Add child to parent's list (convert to 0-based index)
    }
  }
  if ((tsum % 3) != 0) {
    puts("-1");  // If total sum is not divisible by 3, impossible to split
  } else {
    std::vector<long> cuts;
    dfs(root, tsum / 3, h, t, cuts);  // Perform DFS to find cut points
    if (cuts.size() >= 2 && cuts[0] != root && cuts[1] != root) {
      printf("%ld %ld\n", 1 + cuts[0], 1 + cuts[1]);  // Output 1-based indices
    } else {
      puts("-1");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/