// Problem: CF 1421 B - Putting Bricks in the Wall
// https://codeforces.com/contest/1421/problem/B

/*
 * Problem: B. Putting Bricks in the Wall
 * Purpose: Given an n x n grid where S is at (1,1) and F is at (n,n), 
 *          invert at most 2 cells (excluding S and F) such that no path exists 
 *          from S to F regardless of which digit (0 or 1) Roger chooses to traverse.
 *          
 * Algorithm: Analyze four corner cases around the start and end points:
 *            a = v[0][1], b = v[1][0], c = v[n-2][n-1], d = v[n-1][n-2]
 *            These represent the values of the cells adjacent to S and F.
 *            Based on combinations of these 4 bits, determine how many cells to flip
 *            and which ones to flip.
 *
 * Time Complexity: O(n^2) per test case - reading input and checking four corners.
 * Space Complexity: O(n^2) for storing the grid.
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    // Extracting four key corner values
    long a = (v[0][1] - '0');  // value at [0][1] 
    long b = (v[1][0] - '0');  // value at [1][0]
    long c = (v[n - 2][n - 1] - '0');  // value at [n-2][n-1]
    long d = (v[n - 1][n - 2] - '0');  // value at [n-1][n-2]
    
    if (a == 0 && b == 0 && c == 0 && d == 0) {
      printf("2\n1 2\n2 1\n");
    }
    if (a == 0 && b == 0 && c == 0 && d == 1) {
      printf("1\n%ld %ld\n", n - 1, n);
    }
    if (a == 0 && b == 0 && c == 1 && d == 0) {
      printf("1\n%ld %ld\n", n, n - 1);
    }
    if (a == 0 && b == 0 && c == 1 && d == 1) {
      puts("0");
    }
    if (a == 0 && b == 1 && c == 0 && d == 0) {
      printf("1\n1 2\n");
    }
    if (a == 0 && b == 1 && c == 0 && d == 1) {
      printf("2\n1 2\n%ld %ld\n", n, n - 1);
    }
    if (a == 0 && b == 1 && c == 1 && d == 0) {
      printf("2\n2 1\n%ld %ld\n", n, n - 1);
    }
    if (a == 0 && b == 1 && c == 1 && d == 1) {
      printf("1\n2 1\n");
    }
    if (a == 1 && b == 0 && c == 0 && d == 0) {
      printf("1\n2 1\n");
    }
    if (a == 1 && b == 0 && c == 0 && d == 1) {
      printf("2\n2 1\n%ld %ld\n", n, n - 1);
    }
    if (a == 1 && b == 0 && c == 1 && d == 0) {
      printf("2\n1 2\n%ld %ld\n", n, n - 1);
    }
    if (a == 1 && b == 0 && c == 1 && d == 1) {
      printf("1\n1 2\n");
    }
    if (a == 1 && b == 1 && c == 0 && d == 0) {
      puts("0");
    }
    if (a == 1 && b == 1 && c == 0 && d == 1) {
      printf("1\n%ld %ld\n", n, n - 1);
    }
    if (a == 1 && b == 1 && c == 1 && d == 0) {
      printf("1\n%ld %ld\n", n - 1, n);
    }
    if (a == 1 && b == 1 && c == 1 && d == 1) {
      printf("2\n1 2\n2 1\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/