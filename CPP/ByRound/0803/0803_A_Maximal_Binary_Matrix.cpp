// Problem: CF 803 A - Maximal Binary Matrix
// https://codeforces.com/contest/803/problem/A

/*
 * Problem: Maximal Binary Matrix
 * 
 * Algorithm/Technique: Greedy Construction
 * 
 * Time Complexity: O(n^2) - We iterate through the matrix at most twice,
 *                      once for placing the 1s and once for printing.
 * Space Complexity: O(n^2) - We use a 2D array of size n x n to store the matrix.
 * 
 * Approach:
 * - We want to place k ones in an n x n matrix such that:
 *   1. The matrix is symmetric with respect to the main diagonal.
 *   2. The matrix is lexicographically maximal.
 * 
 * Strategy:
 * - To achieve lexicographically maximal matrix, we should place 1s as early as possible,
 *   i.e., in earlier rows and columns.
 * - Since the matrix must be symmetric, for every (i,j) we set, we also set (j,i).
 * - We prefer placing 1s on the main diagonal first (as they contribute to lexicographic
 *   value more significantly than off-diagonal positions).
 * - Then we process off-diagonal positions in a greedy way, placing pairs in the same row
 *   and their symmetric counterparts in the same column.
 * 
 * Edge Cases:
 * - If k > n*n, impossible to fill the matrix, return -1.
 * - If k is odd and n is even, it's impossible to have a symmetric matrix with an odd number of 1s.
 *   (This case is implicitly handled by the greedy placement logic.)
 */

#include <cstdio>
int i, j, n, k, a[101][101];
int main() {
  scanf("%d%d", &n, &k);
  if (n * n < k)
    return puts("-1");
  for (i = 1; i <= n && k; ++i) {
    // Place one 1 on the diagonal if possible
    if (a[i][i] = 1, !--k)
      break;
    // Place pairs of 1s in symmetric off-diagonal positions
    for (j = i + 1; j <= n && k > 1; ++j)
      a[i][j] = a[j][i] = 1, k -= 2;
  }
  for (i = 1; i <= n; ++i, puts(""))
    for (j = 1; j <= n; ++j)
      printf("%d ", a[i][j]);
}


// https://github.com/VaHiX/CodeForces/