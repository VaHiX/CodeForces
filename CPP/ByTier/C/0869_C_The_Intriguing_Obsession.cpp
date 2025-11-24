// Problem: CF 869 C - The Intriguing Obsession
// https://codeforces.com/contest/869/problem/C

/*
 * Problem: The Intriguing Obsession
 * 
 * Purpose: Calculate the number of valid ways to build bridges between three clusters of islands,
 *          where each cluster has a distinct color (red, blue, purple), and constraints prevent
 *          short paths within same-colored clusters.
 * 
 * Algorithm:
 *   - Use dynamic programming with precomputed values for f[p][q] representing number of valid
 *     bridge configurations between two clusters of sizes p and q.
 *   - For each cluster size pair, compute recurrence:
 *       f[p][q] = (f[p-1][q] + f[p-1][q-1] * q) % M
 *   - Final result combines the number of configurations among all three pairs of clusters.
 * 
 * Time Complexity: O(N^2), where N = 5005, so effectively constant due to fixed-size arrays
 * Space Complexity: O(N^2), for storing dynamic programming table
 */

#include <stdint.h>
#include <stdio.h>
#include <vector>

int main() {
  const int N = 5005;
  const int64_t M = 998244353;
  std::vector<std::vector<int64_t>> f(N, std::vector<int64_t>(N, 0));
  
  // Base cases: for one island in either cluster, the number of valid bridge setups is p+1
  for (int p = 1; p < N; p++) {
    f[1][p] = f[p][1] = p + 1;
  }
  
  // Fill DP table using recurrence relation:
  // f[p][q] = (f[p-1][q] + f[p-1][q-1] * q) % M
  for (int p = 2; p < N; p++) {
    for (int q = 2; q < N; q++) {
      f[p][q] = (f[p - 1][q] + f[p - 1][q - 1] * q % M) % M;
    }
  }
  
  // Read input: number of islands in each color cluster
  int a, b, c;
  scanf("%d %d %d\n", &a, &b, &c);
  
  // Compute total number of valid bridge configurations across all three clusters
  int64_t total = ((f[a][b] * f[a][c] % M) * f[b][c]) % M;
  
  // Output result modulo 998244353
  printf("%lld \n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/