// Problem: CF 1366 C - Palindromic Paths
// https://codeforces.com/contest/1366/problem/C

/*
C. Palindromic Paths
Algorithm: 
  - For each diagonal (sum of row and column indices is constant), we collect counts of 0s and 1s.
  - For each pair of diagonals that are symmetric with respect to the center path from (1,1) to (n,m),
    we calculate the minimum flips needed to make all corresponding elements equal.
  - Time Complexity: O(n * m)
  - Space Complexity: O(n + m)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long nr, nc;
    scanf("%ld %ld", &nr, &nc);
    std::vector<long> sv(nr + nc - 1), zv(nr + nc - 1); // sv: count of 1s, zv: count of 0s per diagonal
    for (long row = 0; row < nr; row++) {
      for (long col = 0; col < nc; col++) {
        int x;
        scanf("%d", &x);
        sv[row + col] += x;           // accumulate 1s in the diagonal
        zv[row + col] += 1 - x;       // accumulate 0s in the diagonal
      }
    }
    long total(0);
    for (long p = 0; 2 * (p + 1) < nr + nc; p++) {
      // For each symmetric pair of diagonals, compute minimum flips needed
      long ones = sv[p] + sv[nr + nc - 2 - p];   // total 1s in symmetric diagonals
      long zeros = zv[p] + zv[nr + nc - 2 - p];  // total 0s in symmetric diagonals
      total += (ones < zeros) ? ones : zeros;    // choose smaller count to minimize flips
    }
    printf("%ld\n", total);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/