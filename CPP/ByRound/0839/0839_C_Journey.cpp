// Problem: CF 839 C - Journey
// https://codeforces.com/contest/839/problem/C

/*
 * Problem: C. Journey
 * 
 * Purpose: Calculate the expected length of a random walk on a tree starting from node 1,
 *          where the walk stops when reaching a node that has been visited before.
 * 
 * Algorithm: 
 *   - Build an adjacency list representation of the tree.
 *   - Perform a recursive DFS to calculate expected distance from root (node 1).
 *   - For each node, if it hasn't been visited yet:
 *       - Mark as visited.
 *       - For each unvisited neighbor:
 *           - Recursively compute expected value from that neighbor.
 *           - Add 1 (edge length) to the recursive result and accumulate.
 *       - Return average of all such values.
 * 
 * Time Complexity: O(n) - Each node and edge is visited once.
 * Space Complexity: O(n) - For adjacency list and recursion stack.
 */

#include <cstdio>
#include <vector>
double averageLength(long node, const std::vector<std::vector<long>> &m,
                     std::vector<bool> &been) {
  if (been[node]) {
    return 0;
  }
  been[node] = 1;
  double num(0), den(0);
  for (long p = 0; p < m[node].size(); p++) {
    long cur = m[node][p];
    if (been[cur]) {
      continue;
    }
    ++den;
    num += (1 + averageLength(cur, m, been));  // Add 1 for edge length, then recurse
  }
  if (den > 0) {
    return (num / den);  // Return expected value
  }
  return 0;
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visited(n + 1, 0);
  double avg = averageLength(1, g, visited);
  printf("%.7lf\n", avg);
  return 0;
}


// https://github.com/VaHiX/CodeForces/