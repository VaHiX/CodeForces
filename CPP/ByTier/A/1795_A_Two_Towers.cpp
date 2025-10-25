// Problem: CF 1795 A - Two Towers
// https://codeforces.com/contest/1795/problem/A

/*
 * Problem: A. Two Towers
 * Purpose: Determine if two towers of blocks (represented by strings of 'B' and 'R') 
 *          can be made "beautiful" by moving top blocks between towers, where a 
 *          beautiful configuration means no two adjacent blocks have the same color.
 *
 * Algorithm:
 * 1. For each test case, reverse the second string and append it to the first.
 * 2. Check if there exists any consecutive identical characters in the combined string.
 *    If yes, return "NO"; otherwise, return "YES".
 *
 * Time Complexity: O(n + m) per test case, where n and m are lengths of the two strings.
 * Space Complexity: O(n + m) for the combined string storage.
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string a, b;
    std::cin >> a >> b;
    std::reverse(b.begin(), b.end()); // Reverse second tower and append to first
    a += b; // Combine the two towers (reversed second one appended)
    bool first(false), possible(true);
    for (long p = 1; possible && p < a.size(); p++) {
      bool same = (a[p] == a[p - 1]); // Check if adjacent characters are same
      if (first && same) { // If we've seen a pair of same chars before and current is same
        possible = false;  // Then it's impossible to make it beautiful
        break;
      } else if (same) {
        first = true; // Mark that we have encountered a same character pair
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/