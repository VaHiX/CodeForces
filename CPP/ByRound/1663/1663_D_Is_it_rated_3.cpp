// Problem: CF 1663 D - Is it rated - 3
// https://codeforces.com/contest/1663/problem/D

/*
Problem: D. Is it rated - 3
Algorithm: Conditional logic evaluation
Time Complexity: O(1) - Constant time comparison operations
Space Complexity: O(1) - Fixed space usage for string and integer variables

This program determines whether a contest should be rated based on:
- For "ABC" contests: rated if X < 2000
- For "ARC" contests: rated if X < 2800  
- For "AGC" contests: rated if X >= 1200
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::string s;           // Read contest type (ABC, ARC, or AGC)
  std::cin >> s;
  long x;                  // Read rating value
  std::cin >> x;
  // Evaluate conditions and output "yes" if any condition is met, otherwise "no"
  puts(((s == "ABC" && x < 2000) || (s == "ARC" && x < 2800) ||
        (s == "AGC" && x >= 1200))
           ? "yes"
           : "no");
}


// https://github.com/VaHiX/codeForces/