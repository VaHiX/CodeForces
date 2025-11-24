// Problem: CF 1772 A - A+B?
// https://codeforces.com/contest/1772/problem/A

/* 
 * Code Purpose: This program reads multiple arithmetic expressions of the form "a+b" 
 * where a and b are single digit integers (0-9), evaluates them, and prints the results.
 * 
 * Algorithms/Techniques: String parsing and character to integer conversion using ASCII values
 * 
 * Time Complexity: O(t) where t is the number of test cases, as we process each test case in constant time
 * Space Complexity: O(1) as we only use a fixed amount of extra space regardless of input size
 */

#include <iostream>
#include <string>

int main() {
  int t;
  std::cin >> t;  // Read number of test cases
  while (t--) {   // Process each test case
    std::string s;
    std::cin >> s;  // Read the expression string
    // Extract first digit (s[0]), second digit (s[2]), convert to integers and add
    std::cout << (s[0] - '0' + s[2] - '0') << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/