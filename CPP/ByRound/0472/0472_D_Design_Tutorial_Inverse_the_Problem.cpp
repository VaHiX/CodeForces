// Problem: CF 472 D - Design Tutorial: Inverse the Problem
// https://codeforces.com/contest/472/problem/D

/*
 * Problem: D. Design Tutorial: Inverse the Problem
 * Task: Determine if a given n x n matrix can be the distance matrix of a weighted tree with positive edge weights.
 *
 * Algorithm:
 * - Check basic properties of a distance matrix for a tree:
 *   1. Diagonal elements must be zero (distance from node to itself).
 *   2. Matrix must be symmetric (d[i][j] == d[j][i]).
 *   3. All distances must be positive (except diagonal).
 * - For each node, find the nearest neighbor.
 * - Verify that for every node and its closest neighbor, the triangle inequality holds:
 *   For any pair of nodes u,v, and their closest node w: 
 *   d[u][v] = |d[u][w] - d[v][w]| must hold (i.e., triangle equality).
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<std::vector<long>> distance(n + 1, std::vector<long>(n + 1, 0));
  for (long row = 1; row <= n; row++) {
    for (long col = 1; col <= n; col++) {
      scanf("%ld", &distance[row][col]); // Read matrix entries
    }
  }
  bool possible = 1;
  for (long row = 1; row <= n; row++) {
    if (!possible) {
      break;
    }
    if (distance[row][row] != 0) { // Check that diagonal is zero
      possible = 0;
      break;
    }
    for (long col = row + 1; col <= n; col++) {
      if (distance[row][col] != distance[col][row] || distance[row][col] == 0) { // Check symmetry and positivity
        possible = 0;
        break;
      }
    }
  }
  for (long node = 1; node <= n; node++) {
    if (!possible) {
      break;
    }
    long closest = 1;
    for (long other = 1; other <= n; other++) {
      if (node == other) {
        continue;
      }
      if (distance[node][other] < distance[node][closest]) { // Find closest node to 'node'
        closest = other;
      }
    }
    for (long other = 1; other <= n; other++) {
      long current = distance[node][other] - distance[other][closest];
      if (current < 0) {
        current = -current;
      }
      if (distance[node][closest] != current) { // Check triangle inequality
        possible = 0;
        break;
      }
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/