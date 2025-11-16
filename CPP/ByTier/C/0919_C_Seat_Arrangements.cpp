// Problem: CF 919 C - Seat Arrangements
// https://codeforces.com/contest/919/problem/C

/*
Algorithm/Techniques: 
- The solution scans the classroom grid twice: once for each row and once for each column.
- For each row/column, it counts consecutive empty seats ('.') and whenever a sequence of at least k consecutive empty seats is found, 
  it adds the number of ways to choose k consecutive seats from that sequence to the result.
- The formula `cur - k + 1` gives the number of valid k-length windows in a sequence of length `cur`.
- A special case is handled when k=1, where we divide the result by 2 to avoid double counting (since each seat can be counted in both a row and column).

Time Complexity: O(n * m) - Each cell is processed a constant number of times.
Space Complexity: O(n * m) - To store the matrix of seats.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::string> rm(n);
  for (long p = 0; p < n; p++) {
    std::cin >> rm[p];
  }
  long total(0);
  // Process each row to find consecutive empty seats
  for (long row = 0; row < n; row++) {
    long cur(0);
    for (long col = 0; col < m; col++) {
      if (rm[row][col] == '*') {
        // If we have a sequence of at least k empty seats, count how many k-length windows fit
        if (cur >= k) {
          total += cur - k + 1;
        };
        cur = 0;
      } else {
        ++cur; // Extend current sequence of empty seats
      }
    }
    // Check for remaining sequence at end of row
    if (cur >= k) {
      total += cur - k + 1;
    }
  }
  // Process each column to find consecutive empty seats
  for (long col = 0; col < m; col++) {
    long cur(0);
    for (long row = 0; row < n; row++) {
      if (rm[row][col] == '*') {
        // If we have a sequence of at least k empty seats, count how many k-length windows fit
        if (cur >= k) {
          total += cur - k + 1;
        };
        cur = 0;
      } else {
        ++cur; // Extend current sequence of empty seats
      }
    }
    // Check for remaining sequence at end of column
    if (cur >= k) {
      total += cur - k + 1;
    }
  }
  // Special handling for k=1 to avoid double counting (each seat is counted twice: once in row and once in column)
  if (k == 1) {
    total /= 2;
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/