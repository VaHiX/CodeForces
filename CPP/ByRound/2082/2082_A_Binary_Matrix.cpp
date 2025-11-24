// Problem: CF 2082 A - Binary Matrix
// https://codeforces.com/contest/2082/problem/A

/*
 * Problem: Minimum changes to make a binary matrix "good"
 * A matrix is "good" if the XOR of all elements in each row and column equals 0.
 *
 * Algorithm:
 * - For each row, compute the sum of its elements (since XOR = sum % 2 for binary)
 * - For each column, compute the sum of its elements
 * - Count how many rows/columns have odd sums (these are "bad")
 * - The answer is the maximum of bad rows and bad columns
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for storing the matrix
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> mat(n);
    for (long row = 0; row < n; row++) {
      std::cin >> mat[row]; // Read the matrix row by row
    }
    long rowcnt(0);
    for (long row = 0; row < n; row++) {
      long cnt(0);
      for (long col = 0; col < m; col++) {
        cnt += (mat[row][col] - '0'); // Convert char to int and accumulate
      }
      rowcnt += (cnt % 2); // If sum is odd, increment row counter
    }
    long colcnt(0);
    for (long col = 0; col < m; col++) {
      long cnt(0);
      for (long row = 0; row < n; row++) {
        cnt += (mat[row][col] - '0'); // Convert char to int and accumulate
      }
      colcnt += (cnt % 2); // If sum is odd, increment column counter
    }
    printf("%ld\n", (rowcnt > colcnt ? rowcnt : colcnt)); // Output the larger count
  }
}


// https://github.com/VaHiX/codeForces/