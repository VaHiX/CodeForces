// Problem: CF 1913 A - Rating Increase
// https://codeforces.com/contest/1913/problem/A

/*
 * Problem: A. Rating Increase
 * 
 * Purpose: Given a string formed by concatenating two numbers `a` and `b` (a < b),
 * determine if it's possible to split the string into two valid numbers satisfying 
 * the constraints: no leading zeros, both > 0, and a < b.
 * 
 * Approach:
 * - Try all possible positions to split the string into two parts.
 * - For each split:
 *   - Ensure that neither part has a leading zero.
 *   - Convert both parts to integers.
 *   - Check if a < b.
 * - Return the first valid split found.
 * 
 * Time Complexity: O(n^2), where n is the length of the string. The outer loop runs up to n-1,
 * and for each iteration, string operations are O(n).
 * Space Complexity: O(n), due to storing the input string.
 * 
 * Algorithms/Techniques: Brute-force string splitting with conversion and validation.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool possible(false);
    long a(0), b(0);
    for (long p = 1; p < s.size(); p++) {
      // Skip positions where the second part starts with '0' (leading zero)
      if (s[p] == '0') {
        continue;
      }
      // Extract the first number (from start to position p)
      a = std::stol(s.substr(0, p));
      // Extract the second number (from position p to end)
      b = std::stol(s.substr(p));
      // Check if first number is less than second
      if (a < b) {
        possible = true;
        break;
      }
    }
    if (possible) {
      std::cout << a << " " << b << std::endl;
    } else {
      std::cout << -1 << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/