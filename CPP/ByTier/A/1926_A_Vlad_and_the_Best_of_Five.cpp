// Problem: CF 1926 A - Vlad and the Best of Five
// https://codeforces.com/contest/1926/problem/A

#include <iostream>
#include <string>

/*
 * Problem: A. Vlad and the Best of Five
 * Purpose: Determine which character ('A' or 'B') appears more frequently in a 5-character string.
 * Algorithm: Count occurrences of each character and return the one with higher count.
 * Time Complexity: O(n) where n is the length of the string (constant 5 in this case)
 * Space Complexity: O(1) - only using constant extra space for counters
 */
int main() {
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {   // Process each test case
    std::string s;
    std::cin >> s;  // Read the 5-character string
    long a(0), b(0);  // Initialize counters for 'A' and 'B'
    for (long p = 0; p < s.size(); p++) {  // Iterate through each character
      a += (s[p] == 'A');  // Increment 'a' if current char is 'A'
      b += (s[p] == 'B');  // Increment 'b' if current char is 'B'
    }
    std::cout << (a > b ? 'A' : 'B') << std::endl;  // Output character with higher count
  }
}

// https://github.com/VaHiX/codeForces/