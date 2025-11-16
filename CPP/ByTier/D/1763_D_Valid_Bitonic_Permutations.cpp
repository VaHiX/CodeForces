// Problem: CF 1763 D - Valid Bitonic Permutations
// https://codeforces.com/contest/1763/problem/D

/*
 * Problem: Valid Bitonic Permutations
 * Algorithm: Dynamic Programming with State Compression
 * 
 * This code counts the number of bitonic permutations of numbers 1 to n,
 * such that B[i] = x and B[j] = y. A bitonic permutation increases to a peak
 * and then decreases.
 * 
 * Approach:
 * - Use dynamic programming where f[i][j] represents number of ways
 *   to form a valid bitonic sequence ending at position i with peak at j.
 * - For each step, we try to extend both left and right to grow the sequence.
 * - The function E checks if current position and value assignment is valid
 *   according to constraints.
 * 
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */
#include <stdio.h>
#include <string.h>

typedef long long L;
const L P = 1000000007;
L f[110][110], n, A, B, C, D;
// E checks if the given position and value combination is valid
bool E(L x, L y) { return !(x == A && y != C) && !(x == B && y != D); }
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(f, 0, sizeof(f));
    scanf("%lld%lld%lld%lld%lld", &n, &A, &B, &C, &D);
    // Initialize base cases for valid peaks
    for (L i = 2; i < n; ++i)
      if (E(i, n))
        f[i][i] = 1;
    // Dynamic programming step
    for (L p = 1; p < n; ++p) {
      for (L i = 1, j = p; j <= n; ++i, ++j) {
        // Extend to the left if valid
        if (i > 1 && E(i - 1, n - p))
          f[i - 1][j] = (f[i - 1][j] + f[i][j]) % P;
        // Extend to the right if valid
        if (j < n && E(j + 1, n - p))
          f[i][j + 1] = (f[i][j + 1] + f[i][j]) % P;
      }
    }
    printf("%lld\n", f[1][n]);
  }
}


// https://github.com/VaHiX/CodeForces/