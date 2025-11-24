// Problem: CF 1696 F - Tree Recovery
// https://codeforces.com/contest/1696/problem/F

#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int N = 105;
int n, a[N][N][N], vis[N], d[N][N];
string G[N];

// Function to build the tree structure using DFS
// x: current node, fa: parent node
// Returns 1 if a cycle is detected, 0 otherwise
int build(int x, int fa) {
  for (int y = 1; y <= n; y++)
    // Check if the distance condition is satisfied for node y
    if (a[fa][y][x]) {
      // If already visited, a cycle is detected
      if (vis[y])
        return 1;
      vis[y] = 1;
      // Add edge between x and y
      G[x] += y;
      G[y] += x;
      // Recursively build the tree
      if (build(y, x))
        return 1;
    }
  return 0;
}

// DFS to compute distances from a root node to all other nodes
void dfs(int x, int fa, int rt) {
  for (int y : G[x]) {
    // Skip the parent node
    if (y == fa)
      continue;
    // Update the distance from root (rt) to node y
    d[rt][y] = d[rt][x] + 1;
    dfs(y, x, rt);
  }
}

// Function to validate if a tree with root p is consistent with the input data
bool check(int p) {
  // Reset visited array
  memset(vis + 1, 0, sizeof(int) * n);
  // Clear the edge list for all nodes
  for (int i = 1; i <= n; i++)
    G[i] = "";
  // Mark root and p as visited
  vis[1] = vis[p] = 1;
  // Add edges between root (1) and p
  G[1] += p;
  G[p] += 1;
  // Build the tree starting from 1 and p
  if (build(1, p) || build(p, 1))
    return 0;
  // Check if all nodes are reachable
  for (int i = 1; i <= n; i++) {
    if (!vis[i])
      return 0;
    // Compute all distances from node i
    dfs(i, 0, i);
  }
  // Validate if all distance conditions are satisfied
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        // Check if d[i][k] == d[j][k] matches the input data
        if (d[i][k] == d[j][k] ^ a[i][j][k])
          return 0;
  return 1;
}

// Main function to solve the problem
void solve() {
  cin >> n;
  char z;
  int x;
  // Read input data into a 3D array
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      for (int k = 1; k <= n; k++) {
        cin >> z;
        x = z - '0';
        a[i][j][k] = a[j][i][k] = x;
      }
  // Try each node as a possible root
  for (int i = 2; i <= n; i++)
    if (check(i)) {
      cout << "Yes\n";
      // Print the edges of the tree
      for (int x = 1; x <= n; x++)
        for (int y : G[x])
          if (x < y)
            cout << x << ' ' << y << "\n";
      return;
    }
  cout << "No\n";
}

int main() {
  int tt;
  cin >> tt;
  while (tt--)
    solve();
}

// ### Complexity Analysis:

// - **Time Complexity**: O(n^4)
//   - The input parsing takes O(n^3).
//   - For each possible root node (up to n - 1), the `check` function runs in
//   O(n^3) time (building tree and validating distances).
//   - Combined, this results in O(n^4) overall.
// - **Space Complexity**: O(n^3)
//   - Storage for the 3D array `a[i][j][k]` is O(n^3).
//   - Additional space for adjacency list `G`, `vis`, and distance matrix `d`
//   is O(n^2).
//   - Hence, the total space complexity is O(n^3).

// https://github.com/VaHiX/CodeForces/