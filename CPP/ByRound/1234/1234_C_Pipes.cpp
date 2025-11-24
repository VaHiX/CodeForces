// Problem: CF 1234 C - Pipes
// https://codeforces.com/contest/1234/problem/C

#include <iostream>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    long n;
    std::cin >> n;
    std::string s[2];
    std::cin >> s[0] >> s[1];
    bool possible(true);
    int row(0), col(0), prev(0), next(0);
    while (col < n) {
      // If we are on the same row as previous and current pipe allows flow
      if (prev == row && (s[row][col] == '1' || s[row][col] == '2')) {
        next = row;
        ++col;
      } else if (prev == row) {
        // Switch to other row because current pipe doesn't allow flow
        next = 1 - row;
      } else if (prev != row && (s[row][col] == '1' || s[row][col] == '2')) {
        // If we are switching rows but the pipe in new row blocks the path
        possible = false;
        break;
      } else if (prev != row) {
        // We are on a different row and current pipe allows flow, continue without changing row
        ++col;
        next = row;
      }
      prev = row;
      row = next;
    }
    // Check if we ended up at the bottom row (row 1)
    possible = possible && (next == 1);
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/