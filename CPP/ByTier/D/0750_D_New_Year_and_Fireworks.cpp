// Problem: CF 750 D - New Year and Fireworks
// https://codeforces.com/contest/750/problem/D

/*
 * Purpose: This program calculates the number of unique cells visited by a recursively exploding firework.
 *          The firework starts at the center of an infinite grid and moves in 8 directions (like a chess knight).
 *          At each level of recursion, each part splits into two new parts moving in directions changed by 45 degrees.
 *          The movement at each level is tracked using DFS to avoid double-counting.
 *
 * Algorithms/Techniques:
 *   - Depth-First Search (DFS) to simulate the fireworks explosion path.
 *   - Bitmasking or directional indexing using an array of 8 directions.
 *   - 4D usage of a visited array to prevent recomputation.
 *
 * Time Complexity: O(S * 2^n), where S is the sum of all t_i values, and n is the recursion depth.
 *                    Since t_i <= 5 and n <= 30, S is at most 150. The exponential behavior comes from 2^n splits.
 *
 * Space Complexity: O(N^2 * n * 8), where N = 410, n = 30. The space is dominated by the 4D used array.
 */

#include <cstdio>
#include <vector>
const int N = 410;
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}; // Directional dx for 8 directions
const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1}; // Directional dy for 8 directions
int used[N][N][31][9]; // Tracks visited states: [x][y][depth][direction]
int a[N][N]; // Grid to mark visited cells
int t[N]; // Array to store t_i values

// Recursive DFS to simulate the firework movement and explosion
void dfs(int x, int y, int d, int dir, const std::vector<int> &t) {
  if (d >= t.size()) { // Base case: reached the maximum depth
    return;
  }
  if (used[x][y][d][dir]) { // If already processed this state, skip
    return;
  }
  used[x][y][d][dir] = 1; // Mark this state as visited

  // Mark all t[d] cells in the current direction
  for (int p = 1; p <= t[d]; p++) {
    a[x + dx[dir] * p][y + dy[dir] * p] = 1;
  }

  // Continue recursion with two new directions (rotated left and right by 45 degrees)
  dfs(x + dx[dir] * t[d], y + dy[dir] * t[d], d + 1, (dir + 1) % 8, t); // Move right
  dfs(x + dx[dir] * t[d], y + dy[dir] * t[d], d + 1, (dir + 7) % 8, t); // Move left (equivalent to -1 mod 8)
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> t(n);
  for (int p = 0; p < n; p++) {
    scanf("%d", &t[p]);
  }
  dfs(N / 2, N / 2, 0, 0, t); // Start from center, facing up (direction 0)
  long count = 0;
  for (int x = 0; x < N; x++) {
    for (int y = 1; y < N; ++y) { // Start from y=1 to avoid potential boundary issues
      count += a[x][y];
    }
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/