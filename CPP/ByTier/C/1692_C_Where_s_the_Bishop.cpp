// Problem: CF 1692 C - Where's the Bishop?
// https://codeforces.com/contest/1692/problem/C

/*
C. Where's the Bishop?
Purpose: Given an 8x8 chessboard where '#' represents squares attacked by a single bishop (not on the edges), find the position of that bishop.
Algorithm: Brute force search through all possible internal positions (2 to 7 for both row and column). For each candidate position, check if it forms a valid center for a cross pattern of '#' characters around it.
Time Complexity: O(1) - Since board size is fixed at 8x8, the number of operations is constant.
Space Complexity: O(1) - Only use fixed-size data structures regardless of input.

Input Format:
- t test cases
- Each case has 8 lines with 8 characters each ('.' or '#')

Output Format:
- Two integers r and c representing row and column of the bishop (2 <= r,c <= 7)
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
int main() {
  const int N = 8;
  long t;
  std::cin >> t;
  while (t--) {
    std::vector<std::string> b(N); // Store the 8x8 board
    long row(0), col(0); // To store the result position of bishop
    for (long p = 0; p < N; p++) {
      std::cin >> b[p]; // Read each line of the board
    }
    for (long p = 1; p + 1 < N; p++) { // Loop over internal rows (2 to 7)
      for (long q = 1; q + 1 < N; q++) { // Loop over internal columns (2 to 7)
        if (b[p][q] != '#') { // If current cell is not part of the attack pattern
          continue; // Skip to next cell
        }
        // Check all four diagonal neighbors for presence of '#'
        if (b[p + 1][q + 1] != '#') {
          continue;
        }
        if (b[p + 1][q - 1] != '#') {
          continue;
        }
        if (b[p - 1][q + 1] != '#') {
          continue;
        }
        if (b[p - 1][q - 1] != '#') {
          continue;
        }
        // If all diagonals around current point are '#', this is the bishop's location
        row = p + 1; // Convert from 0-based to 1-based indexing
        col = q + 1;
      }
    }
    printf("%ld %ld\n", row, col); // Print the result
  }
}


// https://github.com/VaHiX/codeForces/