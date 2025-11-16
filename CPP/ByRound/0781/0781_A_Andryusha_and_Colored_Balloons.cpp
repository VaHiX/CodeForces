// Problem: CF 781 A - Andryusha and Colored Balloons
// https://codeforces.com/contest/781/problem/A

/*
Code Purpose:
This code solves the problem of coloring the nodes of a tree such that no three consecutive nodes (in a path) have the same color, 
and it minimizes the number of colors used. It uses a depth-first search (DFS) to assign colors greedily.

Algorithm:
- Build an adjacency list representation of the tree from input.
- Start coloring from node 1 with color 1.
- For each node, traverse its neighbors and assign the smallest valid color 
  (i.e., different from parent and current node) that hasn't been used yet.
- Track the maximum color used to output the minimum number of colors.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
void dfs(const std::vector<std::vector<long>> &g, std::vector<long> &cols,
         long node, long parent, long &maxColor) {
  long nextcol(1);  // Start checking from color 1
  for (long p = 0; p < g[node].size(); p++) {
    long nextNode = g[node][p];
    if (cols[nextNode] > 0) {
      continue;  // Skip already colored nodes
    }
    // Find the smallest color not used by parent or current node
    while (nextcol == cols[parent] || nextcol == cols[node]) {
      ++nextcol;
    }
    maxColor = (maxColor > nextcol) ? maxColor : nextcol;  // Update max color used
    cols[nextNode] = nextcol++;  // Assign color and increment for next use
    dfs(g, cols, nextNode, node, maxColor);  // Recursive DFS on child node
  }
  return;
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
  std::vector<long> color(n + 1, 0);  // Color array initialized to 0
  color[1] = 1;  // Initialize root with color 1
  long numcols(0);  // Track maximum color used
  dfs(g, color, 1, 0, numcols);  // Start DFS from node 1
  printf("%ld\n", numcols);
  for (int p = 1; p <= n; p++) {
    printf("%ld ", color[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/