// Problem: CF 1881 A - Don't Try to Count
// https://codeforces.com/contest/1881/problem/A

/*
 * Problem: Given a string x and a string s, find the minimum number of operations
 *          such that s appears as a substring in x after applying operations.
 *          Each operation appends x to itself.
 *
 * Algorithm:
 *   - For each test case, simulate appending x to itself up to 6 times (since n*m <= 25,
 *     and we can derive an upper bound of 6 operations).
 *   - At each step, check if s is a substring of x using find().
 *   - If found, return the number of operations.
 *   - If not found after 6 steps, return -1.
 *
 * Time Complexity: O(6 * n * m) = O(n * m) since we iterate at most 6 times
 * Space Complexity: O(n + m) for storing x and s
 */
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string x;
    std::cin >> x;
    std::string s;
    std::cin >> s;
    int cnt(-1);
    for (long p = 0; p <= 6; p++) {  // Try up to 6 operations
      if (x.find(s) != std::string::npos) {  // Check if s is substring of x
        cnt = p;
        break;
      }
      x = x + x;  // Append x to itself (operation)
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/