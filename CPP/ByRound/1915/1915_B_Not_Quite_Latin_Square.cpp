// Problem: CF 1915 B - Not Quite Latin Square
// https://codeforces.com/contest/1915/problem/B

/*
Problem: B. Not Quite Latin Square
Purpose: Given a 3x3 grid with one missing letter (represented by '?'), determine the missing letter such that each row and column contains all three letters A, B, C exactly once.

Algorithms/Techniques:
- For each test case, iterate through rows and check for missing letters.
- For each row, count occurrences of 'A', 'B', 'C'.
- If any letter is missing in a row, that is the missing letter.
- Time Complexity: O(1) per test case (since grid size is fixed 3x3).
- Space Complexity: O(1) (constant space usage).

Input:
- t: number of test cases
- For each test case, three rows of 3 characters each (A, B, C, or ?)

Output:
- The missing letter for each test case.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    char m('A'); // Initialize result character to 'A'
    for (long row = 0; row < 3; row++) {
      std::string s;
      std::cin >> s; // Read the current row
      bool a(false), b(false), c(false); // Flags to track presence of letters in current row
      for (long col = 0; col < 3; col++) {
        if (s[col] == 'A') {
          a = true;
        } else if (s[col] == 'B') {
          b = true;
        } else if (s[col] == 'C') {
          c = true;
        }
      }
      // If any letter is missing in the row, it must be the one replaced by '?'
      if (!a) {
        m = 'A';
      } else if (!b) {
        m = 'B';
      } else if (!c) {
        m = 'C';
      }
    }
    std::cout << m << std::endl; // Output the missing letter
  }
}


// https://github.com/VaHiX/codeForces/