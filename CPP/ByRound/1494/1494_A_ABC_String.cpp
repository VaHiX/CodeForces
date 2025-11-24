// Problem: CF 1494 A - ABC String
// https://codeforces.com/contest/1494/problem/A

/*
 * Problem: ABC String
 * Purpose: Determine if a string consisting of 'A', 'B', 'C' can be converted to a valid bracket sequence
 *          by replacing each character with either '(' or ')'
 * 
 * Algorithm:
 * 1. For each test case, try all valid assignments of brackets to letters A, B, C
 * 2. Use a greedy approach where we assign values to first and last character's letter,
 *    then deduce the rest based on how many times each letter appears
 * 3. Validate if the resulting sequence is a valid bracket sequence using cumulative sum
 * 
 * Time Complexity: O(n) per test case, where n is the length of string
 * Space Complexity: O(1) - Only fixed size arrays and variables used
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    int f[3] = {0}; // Array to store bracket values for A, B, C
    f[s[0] - 'A'] = 1;  // Assign +1 to first character's letter
    f[s.back() - 'A'] = -1;  // Assign -1 to last character's letter
    long cnt(0);
    for (long p = 0; p < s.size(); p++) {
      cnt += f[s[p] - 'A']; // Count cumulative sum of bracket values
    }
    for (long p = 0; p < 3; p++) {
      if (f[p] == 0) {
        // If letter wasn't assigned in first/last, assign based on total count
        f[p] = 1 - 2 * (cnt > 0);
      }
    }
    cnt = 0;
    std::string res("YES");
    for (long p = 0; p < s.size(); p++) {
      cnt += f[s[p] - 'A']; // Update cumulative bracket count
      if (cnt < 0) {        // If balance goes negative, invalid sequence
        res = "NO";
        break;
      }
    }
    if (cnt) {                // If final balance is not zero, invalid sequence
      res = "NO";
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/