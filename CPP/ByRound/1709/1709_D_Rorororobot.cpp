// Problem: CF 1709 D - Rorororobot
// https://codeforces.com/contest/1709/problem/D

/*
 * Problem: D. Rorororobot
 * 
 * Purpose: Determine if a robot can reach from a start position to a finish position
 *          in a grid with blocked cells, where each command is executed k times.
 *          The grid has n rows and m columns, and each column has a_i bottom cells blocked.
 * 
 * Algorithm: 
 * - Use a sparse table for range maximum queries (RMQ) to efficiently compute
 *   the maximum number of blocked cells in any contiguous range of columns.
 * - For each query, check if:
 *   1. The difference in row and column coordinates is divisible by k (to ensure
 *      that the robot can reach the destination with integer steps).
 *   2. The robot can actually reach the destination given the blocked ranges
 *      by comparing the maximum blocked height in the path with the required
 *      vertical distance.
 * 
 * Time Complexity: 
 *   - Preprocessing (sparse table): O(m * log m)
 *   - Each query: O(1)
 *   - Total: O(m * log m + q)
 * 
 * Space Complexity: O(m * log m)
 */

#include <stdio.h>
#include <algorithm>
#include <cmath>

#define N 200005
using namespace std;

int n, m, a[N][20], q;

// Function to perform range maximum query using sparse table
int ask(int l, int r) {
  int k = log2(r - l + 1);  // Determine the highest power of 2 that fits in [l, r]
  return max(a[l][k], a[r - (1 << k) + 1][k]);  // Return max of two overlapping segments
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++)
    scanf("%d", &a[i][0]);  // Read initial blocked heights for each column
  
  // Build sparse table for range maximum queries
  for (int i = 1; (1 << i) <= m; i++)
    for (int j = 1; j + (1 << i) - 1 <= m; j++)
      a[j][i] = max(a[j][i - 1], a[j + (1 << (i - 1))][i - 1]);
  
  scanf("%d", &q);
  while (q--) {
    int x, y, X, Y, k;
    scanf("%d%d%d%d%d", &x, &y, &X, &Y, &k);
    
    // Check if the move is possible with k-step increments
    // Also check the maximum blocked height in the vertical path
    puts((x - X) % k == 0 && (y - Y) % k == 0 &&
         (n - x) / k * k + x > ask(min(y, Y), max(y, Y))  // Check if path is valid
         ? "YES"
         : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/