// Problem: CF 1966 B - Rectangle Filling
// https://codeforces.com/contest/1966/problem/B

/*
B. Rectangle Filling
Algorithm: For each color (W and B), find the minimum and maximum row and column indices that contain squares of that color. 
The grid can be filled to a single color if and only if one of the following is true:
1. All W's are within a rectangle that covers all rows and columns (i.e., min_row=0, max_row=n-1, min_col=0, max_col=m-1).
2. All B's are within a rectangle that covers all rows and columns.
Time Complexity: O(n * m) per test case
Space Complexity: O(1)
*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    // Initialize variables to track bounding box of W's and B's
    int wmnr(n + 1), bmnr(n + 1), wmxr(-1), bmxr(-1), wmnc(m + 1), bmnc(m + 1),
        wmxc(-1), bmxc(-1);
    for (long row = 0; row < n; row++) {
      std::string s;
      std::cin >> s;
      for (int col = 0; col < s.size(); col++) {
        if (s[col] == 'W') {
          wmnr = (row < wmnr ? row : wmnr); // Update min row for W
          wmxr = (row > wmxr ? row : wmxr); // Update max row for W
          wmnc = (col < wmnc ? col : wmnc); // Update min col for W
          wmxc = (col > wmxc ? col : wmxc); // Update max col for W
        } else if (s[col] == 'B') {
          bmnr = (row < bmnr ? row : bmnr); // Update min row for B
          bmxr = (row > bmxr ? row : bmxr); // Update max row for B
          bmnc = (col < bmnc ? col : bmnc); // Update min col for B
          bmxc = (col > bmxc ? col : bmxc); // Update max col for B
        }
      }
    }
    bool possible(false);
    // Check if all W's form a rectangle covering whole grid
    if (wmnr == 0 && wmxr == n - 1 && wmnc == 0 && wmxc == m - 1) {
      possible = true;
    }
    // Check if all B's form a rectangle covering whole grid
    if (bmnr == 0 && bmxr == n - 1 && bmnc == 0 && bmxc == m - 1) {
      possible = true;
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/