// Problem: CF 765 B - Code obfuscation
// https://codeforces.com/contest/765/problem/B

/*
 * Problem: Check if a given string can be a result of Kostya's code obfuscation.
 * 
 * Approach:
 * - Simulate the obfuscation process in reverse.
 * - Maintain a variable 'next' representing the next expected character in the sequence ('a', 'b', ..., 'z').
 * - Traverse the input string character by character:
 *   - If current character is less than 'next', it has already been assigned to a previous identifier → skip.
 *   - If equal, increment 'next' to move to the next expected identifier.
 *   - If greater, it violates the order → impossible to be valid obfuscation.
 * 
 * Time Complexity: O(n), where n is the length of the input string. Each character is visited once.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s; // Read input string
  bool possible(true); // Flag to track if valid obfuscation
  char next('a'); // Next expected character in sequence
  for (size_t p = 0; p < s.size(); p++) { // Traverse each character
    if (s[p] < next) {
      continue; // Already assigned, skip
    }
    if (s[p] == next) {
      ++next; // Assign new identifier
    } else {
      possible = false; // Invalid order
      break;
    }
  }
  std::cout << (possible ? "YES" : "NO") << std::endl; // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/