// Problem: CF 1610 I - Mashtali vs AtCoder
// https://codeforces.com/contest/1610/problem/I

/*
 * Problem: Mashtali vs AtCoder - Game on a Tree
 * 
 * Approach:
 * - This is a game theory problem on a tree, using the Sprague-Grundy theorem.
 * - We compute the Grundy number (nimber) for each node using DFS.
 * - The game state is determined by the XOR of all Grundy numbers of the tree components.
 * - For each k (number of pinned vertices from 1 to k), we determine if the first player wins.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Tree DFS traversal
 * - Grundy number computation
 * - Bit manipulation for nim-sum calculations
 */

#include <iostream>
#include <string>

using namespace std;
enum { N = 300009 };
basic_string<int> g[N];
int f[N], s[N];
bool b[N];
void dfs(int x, int y) {
  f[x] = y; // Store parent of x
  for (int i : g[x]) // Iterate through neighbors
    if (i ^ y) // If neighbor is not parent
      dfs(i, x), s[x] ^= s[i] + 1; // Recursively compute and XOR Grundy numbers
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, i, j, k;
  for (cin >> n, i = 1; i < n; ++i) // Read edges
    cin >> j >> k, g[j] += k, g[k] += j; // Build adjacency list
  for (i = 2, dfs(b[1] = 1, 0), j = s[1]; cout << (j == 0) + 1, i <= n; ++i) // Initialize and process each k
    for (k = i; !b[k]; k = f[k]) // Traverse up the tree from vertex i to root
      b[k] = 1, j ^= s[k] ^ s[k] + 1 ^ 1; // Update the nim-sum for the current state
  return 0;
}


// https://github.com/VaHiX/CodeForces/