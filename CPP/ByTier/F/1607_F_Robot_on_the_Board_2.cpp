// Problem: CF 1607 F - Robot on the Board 2
// https://codeforces.com/contest/1607/problem/F

/*
Algorithm: 
This code solves the problem of finding the starting position for a robot on a grid that allows it to take the maximum number of steps before it either falls off the board or enters a cycle.
The approach uses graph traversal with path compression to efficiently compute the number of steps from each starting position.

Techniques:
- Path compression using memoization (f array)
- Forward simulation of robot movements (p array stores next position)
- Union-find like approach with cycle detection

Time Complexity: O(n * m) where n and m are dimensions of the grid
Space Complexity: O(n * m) for storing the grid information and auxiliary arrays

The robot's movements are simulated by:
1. Preprocessing all grid positions into a directed graph where each node points to its next position
2. For each starting position, computing the number of steps using DFS with memoization
3. The path compression ensures each node is visited only once during computation
*/
#include <iostream>

using namespace std;
const int kMaxN = 4e6 + 5;
int t, n, m, p[kMaxN], f[kMaxN];
char c;
int S(int x) {
  // If x is 0, it means we've fallen off the board
  if (x == 0) {
    return 0;
  }
  // If f[x] is 0, it means we haven't computed this node yet
  if (f[x] == 0) {
    int s = 1;
    // Traverse the path until we return to the starting point
    for (int i = p[x]; i != x; i = p[i]) {
      s++;
    }
    // Assign computed steps to all nodes in the cycle
    for (int i = p[x]; i != x; i = p[i]) {
      f[i] = s;
    }
    f[x] = s;
    return s;
  }
  // If we already computed this node, return the stored value
  if (f[x] != -1) {
    return f[x];
  }
  // Mark as being computed
  f[x] = 0;
  // Recursively compute the next position
  S(p[x]);
  // If we haven't finished computing yet, set value based on next node
  if (!f[x]) {
    f[x] = f[p[x]] + 1;
  }
  return f[x];
}
int main() {
  for (cin >> t; t--;) {
    cin >> n >> m;
    // Process each cell of the grid
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> c;
        int x = (i - 1) * m + j;
        f[x] = -1; // Mark as unvisited
        // Set next position based on direction
        (c == 'U') && (p[x] = i > 1 ? x - m : 0);
        (c == 'D') && (p[x] = i < n ? x + m : 0);
        (c == 'L') && (p[x] = j > 1 ? x - 1 : 0);
        (c == 'R') && (p[x] = j < m ? x + 1 : 0);
      }
    }
    int r = 1; // Best starting position
    // Compute steps from each position and find maximum
    for (int i = 1; i <= n * m; i++) {
      S(i);
      (f[i] > f[r]) && (r = i);
    }
    // Output the result in 1-indexed coordinates
    cout << (r - 1) / m + 1 << " " << (r - 1) % m + 1 << " " << f[r] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/