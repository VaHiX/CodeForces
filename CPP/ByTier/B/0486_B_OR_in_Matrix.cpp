// Problem: CF 486 B - OR in Matrix
// https://codeforces.com/contest/486/problem/B

/*
Purpose: This program determines whether a given matrix B can be produced from some binary matrix A
         using the rule that B[i][j] is the OR of all elements in row i and column j of matrix A.
         If possible, it reconstructs one such matrix A; otherwise, it outputs "NO".

Algorithm/Techniques:
- Greedy reconstruction: Start with all 1s in A, then systematically set elements to 0 where needed.
- Validation: For each entry in B equal to 1, verify that there exists at least one 1 in the corresponding row or column of A.

Time Complexity: O(m * n * (m + n)) due to:
                 - Setting zeros in A based on B[0][0] == 0: O(m * n)
                 - Validation of each B[i][j] == 1: O(m * n * (m + n))
Space Complexity: O(m * n) for storing matrices A and B.
*/

#include <cstdio>
#include <vector>
int main() {
  int m, n;
  scanf("%d %d\n", &m, &n);
  std::vector<std::vector<int>> A(m, std::vector<int>(n, 1)); // Initialize A with all 1s
  std::vector<std::vector<int>> B(m, std::vector<int>(n, 0)); // Read B
  for (int row = 0; row < m; row++) {
    for (int col = 0; col < n; col++) {
      scanf("%d", &B[row][col]);
    }
  }
  // Process each element of B to determine if we can zero out parts of A
  for (int bRow = 0; bRow < m; bRow++) {
    for (int bCol = 0; bCol < n; bCol++) {
      if (B[bRow][bCol] == 0) {
        // If B[i][j] = 0, then ALL elements in row i and column j must be 0 in A
        for (int aRow = 0; aRow < m; aRow++) {
          A[aRow][bCol] = 0; // Zero out column bCol
        }
        for (int aCol = 0; aCol < n; aCol++) {
          A[bRow][aCol] = 0; // Zero out row bRow
        }
      }
    }
  }
  bool possible = 1; // Flag to check if solution is valid
  for (int bRow = 0; bRow < m; bRow++) {
    if (!possible) {
      break;
    }
    for (int bCol = 0; bCol < n; bCol++) {
      if (!possible) {
        break;
      }
      if (B[bRow][bCol] == 1) {
        bool isValid = 0;
        // Check if there is at least one 1 in column bCol (before zeroing)
        for (int aRow = 0; aRow < m; aRow++) {
          if (A[aRow][bCol] == 1) {
            isValid = 1;
            break;
          }
        }
        if (isValid) {
          continue; // If valid, proceed
        }
        // Check if there is at least one 1 in row bRow (before zeroing)
        for (int aCol = 0; aCol < n; aCol++) {
          if (A[bRow][aCol] == 1) {
            isValid = 1;
            break;
          }
        }
        if (!isValid) {
          possible = 0; // Invalid configuration
        }
      }
    }
  }
  if (!possible) {
    puts("NO");
  } else {
    puts("YES");
    for (int aRow = 0; aRow < m; aRow++) {
      for (int aCol = 0; aCol < n; aCol++) {
        printf("%d ", A[aRow][aCol]);
      }
      puts("");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/