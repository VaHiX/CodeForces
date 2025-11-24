// Problem: CF 2065 B - Skibidus and Ohio
// https://codeforces.com/contest/2065/problem/B

/*
B. Skibidus and Ohio

Purpose:
This program determines the minimum possible length of a string after performing a series of operations.
Each operation allows replacing a character at index i with any other character, then removing the next character (i+1),
provided that s[i] == s[i+1]. The goal is to reduce the string to its minimal form by repeatedly applying such operations.

Algorithm:
- For each test case:
  - Iterate through the string to find adjacent duplicate characters.
  - If a pair of consecutive equal characters is found, set a flag indicating that a reduction is possible.
  - If no such pairs are found, output the size of the string.
  - Otherwise, output 1 because all characters can be reduced to one character.

Time Complexity: O(n) where n is the length of the string. We perform a single pass through the string for each test case.
Space Complexity: O(1) not counting input/output; only using a few variables for processing.

Techniques:
- Linear scan to detect adjacent duplicates
- Early termination when a duplicate is found

*/

#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s;  // Read the input string
    bool same(false);  // Flag to track if any adjacent duplicates exist
    for (size_t p = 0; !same && p < s.size(); p++) {
      same = (s[p - 1] == s[p]);  // Compare current character with previous one (will be invalid at p=0)
    }
    std::cout << (same ? 1 : s.size()) << std::endl;  // Output result based on whether duplicates were found
  }
}


// https://github.com/VaHiX/codeForces/