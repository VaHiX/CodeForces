// Problem: CF 1322 A - Unusual Competitions
// https://codeforces.com/contest/1322/problem/A

/*
A. Unusual Competitions
Problem Description:
Given a string of parentheses, determine the minimum number of nanoseconds required to make it a correct bracket sequence by performing reorder operations. Each reorder operation on a substring of length l takes l nanoseconds.

Algorithm:
- Traverse the string and track the balance (cs) of open and close brackets.
- When we detect an invalid closing bracket (balance becomes negative), record its position.
- When we encounter an opening bracket that brings balance back to zero, calculate the cost to fix up to that point.
- If final balance is non-zero, it's impossible to make a correct sequence.

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long start(-1), cnt(0), cs(0);
  for (long p = 0; p < s.size(); p++) {
    cs += (s[p] == '(') - (s[p] == ')'); // Update balance: +1 for '(', -1 for ')'
    if (s[p] == ')' && cs == -1) {       // Found an invalid closing bracket
      start = p;                         // Record the position
    } else if (s[p] == '(' && cs == 0) { // Found a valid opening bracket after balance reset
      cnt += (p - start + 1);            // Add cost to fix from last invalid ')' to current '('
    }
  }
  cnt = (cs ? -1 : cnt); // If final balance is not zero, impossible to make correct
  std::cout << cnt << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/