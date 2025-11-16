// Problem: CF 1207 B - Square Filling
// https://codeforces.com/contest/1207/problem/B

/*
B. Square Filling
Algorithms/Techniques: Greedy algorithm, Matrix manipulation
Time Complexity: O(n * m)
Space Complexity: O(n * m)

The problem asks to transform matrix B (initially all zeros) into matrix A using 2x2 submatrix operations.
We use a greedy approach:
1. Scan the matrix from top-left to bottom-right.
2. If we find a position (i,j) where A[i][j] is 1 but B[i][j] is not yet 1, and if we can form a valid 2x2 square,
   then apply operation at that position.
3. After processing all positions, check if B == A.

The greedy strategy ensures that we don't "overpaint" any area because we process from top-left to bottom-right
and only activate areas which are required (when needed to match A).
*/

#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<long>> a(n + 1, std::vector<long>(m + 1, 0));  // Input matrix A
  std::vector<std::vector<long>> b(n + 1, std::vector<long>(m + 1, 0));  // Working matrix B
  std::vector<std::pair<long, long>> ans;  // Stores positions of operations
  for (long p = 1; p <= n; p++) {
    for (long q = 1; q <= m; q++) {
      scanf("%ld", &a[p][q]);  // Read input matrix A
    }
  }
  // Process each potential 2x2 square position
  for (long p = 1; p < n; p++) {  
    for (long q = 1; q < m; q++) {
      // If all four corners of a 2x2 square are 1 in A, we can apply operation here.
      if (a[p][q] == 1 && a[p + 1][q] == 1 && a[p][q + 1] == 1 &&
          a[p + 1][q + 1] == 1) {
        // Update B to reflect that we applied an operation at (p,q)
        b[p][q] = b[p + 1][q] = b[p][q + 1] = b[p + 1][q + 1] = 1;
        ans.push_back(std::make_pair(p, q));  // Record the operation
      }
    }
  }
  // Verify if transformation is possible by checking all positions
  for (long p = 1; p <= n; p++) {
    for (long q = 1; q <= m; q++) {
      if (a[p][q] != b[p][q]) {  // If any cell differs between A and B, impossible
        puts("-1");
        return 0;
      }
    }
  }
  // Output number of operations
  printf("%ld\n", ans.size());
  for (long p = 0; p < ans.size(); p++) {
    printf("%ld %ld\n", ans[p].first, ans[p].second);  // Output positions of operations
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/