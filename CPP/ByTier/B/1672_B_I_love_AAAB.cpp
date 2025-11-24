// Problem: CF 1672 B - I love AAAB
// https://codeforces.com/contest/1672/problem/B

/*
B. I love AAAB
Time Complexity: O(n) where n is the total length of input strings across all test cases
Space Complexity: O(1) excluding input storage

Algorithm:
The problem asks whether a given string can be constructed by inserting "good" strings.
A good string is defined as one that starts with any number of 'A's followed by a single 'B'.
This means a valid sequence must end with 'B' and at no point during traversal should 
the cumulative count of 'A's minus 'B's drop below zero. This is essentially a balanced
parentheses-like check.

Approach:
1. For each test case, we read the string.
2. We verify the last character is 'B'. If not, it's invalid.
3. Traverse from left to right maintaining a counter:
   - Increment counter for each 'A'
   - Decrement for each 'B'
4. If at any point counter becomes negative, it's invalid (more B's than A's so far).
5. If the entire traversal is valid and ends with 'B', return "YES", otherwise "NO".
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  while (n--) {
    std::string s;
    std::cin >> s;
    long cnt(0);
    bool res(true);
    if (s.back() != 'B') { // Check if string ends with 'B'
      res = false;
    }
    for (long p = 0; res && p < s.size(); p++) {
      cnt += (s[p] == 'A') - (s[p] == 'B'); // Increment for A, decrement for B
      if (cnt < 0) { // If at any point we have more B's than A's, invalid
        res = false;
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/