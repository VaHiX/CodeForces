// Problem: CF 1722 B - Colourblindness
// https://codeforces.com/contest/1722/problem/B

/*
B. Colourblindness

Purpose:
This program determines if two rows of a grid are considered the same by a colourblind person who cannot distinguish between green (G) and blue (B).
The solution compares each position in the two strings, accepting G=B and B=G as equivalent.

Algorithm:
- For each test case, compare character-by-character the two input strings.
- Allow G and B to be treated as equal.
- If all positions match under this rule, output "YES", otherwise "NO".

Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(1) additional space (excluding input/output storage).

Techniques:
- String comparison with special handling for 'G' and 'B'
- Early termination on mismatch
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n;  // Read the number of columns
    std::string u, v;
    std::cin >> u >> v;  // Read two rows as strings
    bool res(true);  // Initialize result as true
    for (long p = 0; p < n; p++) {  // Iterate through each column
      if (u[p] == v[p]) {  // If characters are identical
        continue;  // Move to next column
      } else if (u[p] == 'G' && v[p] == 'B') {  // If u is G and v is B
        continue;  // Accept as equal due to colourblindness
      } else if (u[p] == 'B' && v[p] == 'G') {  // If u is B and v is G
        continue;  // Accept as equal due to colourblindness
      }
      res = false;  // Mismatch found
      break;  // Early exit
    }
    std::cout << (res ? "YES" : "NO") << std::endl;  // Output result
  }
}


// https://github.com/VaHiX/codeForces/