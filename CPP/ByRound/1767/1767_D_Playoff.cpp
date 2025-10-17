// Problem: CF 1767 D - Playoff
// https://codeforces.com/contest/1767/problem/D

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n; // Read the number of phases
  std::string s;
  std::cin >> s; // Read the string describing tournament rules
  long ones(0); // Count number of '1' characters in string s
  for (long p = 0; p < s.size(); p++) {
    ones += (s[p] == '1'); // Increment count if current character is '1'
  }
  // Loop through numbers from (1 << ones) to (1 << n) - (1 << (n - ones)) + 1
  for (long p = (1 << ones); p <= (1 << n) - (1 << (n - ones)) + 1; p++) {
    printf("%ld ", p); // Print each valid number
  }
  puts(""); // Print newline at end
  return 0;
}
/*
Flowerbox:
Problem: Playoff
Purpose: Find all integers x such that there exists a permutation of skill levels where team x wins the tournament, given the tournament rules encoded in string s.
Algorithms/Techniques: Bit manipulation, combinatorial analysis to determine valid ranges.
Time Complexity: O(2^n) - due to generating and checking all possible values in the range.
Space Complexity: O(1) - only using fixed amount of extra space.

Note: The actual algorithm leverages the observation that in each phase,
the result depends on whether "0" or "1" is used. The key insight is determining
valid ranges for winning teams based on cumulative binary decisions.
*/

// https://github.com/VaHiX/codeForces/