// Problem: CF 722 A - Broken Clock
// https://codeforces.com/contest/722/problem/A

/*
 * Purpose: This code fixes a broken clock's time to conform to either 12-hour or 24-hour format.
 *          It minimizes the number of digit changes required to make the time valid.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: Fix invalid hours and minutes step by step.
 *   - Direct validation and replacement based on format rules.
 *
 * Time Complexity: O(1) - Constant time operations, as the input size is fixed.
 * Space Complexity: O(1) - Only a fixed amount of extra space is used.
 */

#include <iostream>
#include <string>

int main() {
  std::string t;
  std::cin >> t;
  std::string s;
  std::cin >> s;
  int h = 10 * (s[0] - '0') + (s[1] - '0');  // Extract hours from string
  int m = 10 * (s[3] - '0') + (s[4] - '0');  // Extract minutes from string
  
  // Check if hours are invalid for 24-hour format
  if (t == "24" && h > 23) {
    s[0] = '0';  // Fix the first hour digit to '0' to make it valid
  } 
  // Check if hours are invalid for 12-hour format and second digit is not '0'
  else if (t == "12" && h > 12 && s[1] != '0') {
    s[0] = '0';  // Fix the first hour digit to '0'
  } 
  // Check if hours are invalid for 12-hour format and second digit is '0'
  else if (t == "12" && h > 12 && s[1] == '0') {
    s[0] = '1';  // Fix the first hour digit to '1'
  } 
  // Special case for hours like 00 in 12-hour format (should be 12)
  else if (t == "12" && h == 0) {
    s[1] = '1';  // Fix the second hour digit to '1'
  }
  
  // Check if minutes are invalid (>59)
  if (m > 59) {
    s[3] = '0';  // Fix the first minute digit to '0'
  }
  
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/