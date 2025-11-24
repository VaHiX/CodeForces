// Problem: CF 1512 B - Almost Rectangle
// https://codeforces.com/contest/1512/problem/B

/*
B. Almost Rectangle

Purpose:
This code solves the problem of marking two additional cells in an n×n grid so that the four marked cells form the corners of a rectangle with sides parallel to the coordinate axes.
Given exactly two asterisks ('*') on the grid, we must add two more asterisks to make a valid rectangle.

Algorithms/Techniques:
- Brute-force approach to determine how to place two additional markers
- Check if the existing two stars are in same row or column
- Based on that, decide where to place the other two stars

Time Complexity: O(n^2) per test case - due to scanning the grid twice (once for input and once for finding stars),
                   and placing new stars requires constant time.
Space Complexity: O(n^2) - storing the grid and vector of pairs for star positions.

*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> f(n);
    for (long row = 0; row < n; row++) {
      std::cin >> f[row];
    }
    std::vector<std::pair<long, long>> s; // Store positions of stars
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        if (f[row][col] == '.') {
          continue;
        }
        s.push_back(std::make_pair(row, col)); // Add star position to list
      }
    }
    if (s[0].first == s[1].first) {
      // Stars are in same row - place new stars in next row
      long rr = (1 + s[0].first) % n;
      f[rr][s[0].second] = '*';
      f[rr][s[1].second] = '*';
    } else if (s[0].second == s[1].second) {
      // Stars are in same column - place new stars in next column
      long cc = (1 + s[0].second) % n;
      f[s[0].first][cc] = '*';
      f[s[1].first][cc] = '*';
    } else {
      // Stars are in different row and column - form rectangle using cross positions
      f[s[0].first][s[1].second] = '*';
      f[s[1].first][s[0].second] = '*';
    }
    for (long row = 0; row < n; row++) {
      std::cout << f[row] << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/