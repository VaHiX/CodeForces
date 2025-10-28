// Problem: CF 1703 A - YES or YES?
// https://codeforces.com/contest/1703/problem/A

/*
Problem: A. YES or YES?
Purpose: Check if a 3-character string is "YES" in any case combination.
Algorithm/Techniques: Direct character comparison with case insensitivity.
Time Complexity: O(1) per test case, O(t) overall where t is number of test cases.
Space Complexity: O(1), only using fixed-size variables.

Input:
- First line: integer t (number of test cases)
- Each of the next t lines: a 3-character string consisting of uppercase/lowercase letters

Output:
- For each test case, print "YES" if string matches "YES" in any case, otherwise "NO"
*/

#include <iostream>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) { // Process each test case
    std::string s;
    std::cin >> s; // Read the input string
    bool res(true); // Assume result is true initially
    
    // Check if first character is 'Y' or 'y'
    if (s[0] != 'Y' && s[0] != 'y') {
      res = false; // Mark as false if not matching
    }
    
    // Check if second character is 'E' or 'e'
    if (s[1] != 'E' && s[1] != 'e') {
      res = false; // Mark as false if not matching
    }
    
    // Check if third character is 'S' or 's'
    if (s[2] != 'S' && s[2] != 's') {
      res = false; // Mark as false if not matching
    }
    
    std::cout << (res ? "YES" : "NO") << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/