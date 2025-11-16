// Problem: CF 1983 B - Corner Twist
// https://codeforces.com/contest/1983/problem/B

/*
 * Problem: B. Corner Twist
 * 
 * Algorithm/Technique: 
 * The key insight is that each operation affects four corners of a subrectangle.
 * For any subrectangle, two diagonally opposite corners are incremented by 1 (mod 3)
 * and the other two by 2 (mod 3). 
 * 
 * We can think of this problem in terms of differences:
 * - For each row, the sum of elements contributes to the overall parity.
 * - For each column, the sum of elements contributes to the overall parity.
 * 
 * The core idea is that each operation changes the row/column sums in a specific pattern.
 * Thus, we only need to track the modulo 3 of row and column sums for both grids a and b,
 * and check if they match.
 * 
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n + m) for storing row and column sums.
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
constexpr int kMaxN = 505;
char input[kMaxN];
int a_row[kMaxN];    // Sum of elements in each row of grid a
int a_col[kMaxN];    // Sum of elements in each column of grid a
int b_row[kMaxN];    // Sum of elements in each row of grid b
int b_col[kMaxN];    // Sum of elements in each column of grid b

int main() {
  int nr_tests;
  std::cin >> nr_tests;
  while (nr_tests--) {
    int n, m;
    std::scanf("%d%d", &n, &m);
    // Reset all arrays to 0
    std::fill(a_row, a_row + n, 0);
    std::fill(a_col, a_col + m, 0);
    std::fill(b_row, b_row + n, 0);
    std::fill(b_col, b_col + m, 0);
    
    // Read grid a and accumulate row and column sums
    for (int i = 0; i < n; ++i) {
      std::scanf("%s", input);
      for (int j = 0; j < m; ++j) {
        int x = input[j] - '0';  // Convert char to int
        a_row[i] += x;           // Add to row sum
        a_col[j] += x;           // Add to column sum
      }
    }
    
    // Read grid b and accumulate row and column sums
    for (int i = 0; i < n; ++i) {
      std::scanf("%s", input);
      for (int j = 0; j < m; ++j) {
        int x = input[j] - '0';  // Convert char to int
        b_row[i] += x;           // Add to row sum
        b_col[j] += x;           // Add to column sum
      }
    }
    
    bool fine = true;
    
    // Check if row sums match modulo 3
    for (int i = 0; i < n; ++i) {
      a_row[i] %= 3;
      b_row[i] %= 3;
      fine &= (a_row[i] == b_row[i]);
    }
    
    // Check if column sums match modulo 3
    for (int j = 0; j < m; ++j) {
      a_col[j] %= 3;
      b_col[j] %= 3;
      fine &= (a_col[j] == b_col[j]);
    }
    
    std::printf("%s\n", fine ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/