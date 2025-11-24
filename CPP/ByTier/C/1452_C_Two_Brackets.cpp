// Problem: CF 1452 C - Two Brackets
// https://codeforces.com/contest/1452/problem/C

/*
C. Two Brackets
Purpose: Given a string of brackets, find the maximum number of moves where each move removes a valid bracket subsequence (RBS).
Algorithm: Greedy approach using counters for '(' and '[' brackets.
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) excluding input storage.

Techniques:
- Two-pass greedy algorithm
- Counter-based matching for parentheses and square brackets
- Matching pairs from left to right, removing matched brackets incrementally

*/
#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long na(0), nb(0), cnt(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '(') {           // Increment counter for '('
        ++na;
      } else if (s[p] == '[') {    // Increment counter for '['
        ++nb;
      } else if (s[p] == ')' && na > 0) {  // Match ')' with '(' if available
        ++cnt;
        --na;
      } else if (s[p] == ']' && nb > 0) {  // Match ']' with '[' if available
        ++cnt;
        --nb;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/