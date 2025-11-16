// Problem: CF 1754 A - Technical Support
// https://codeforces.com/contest/1754/problem/A

/*
Purpose: Determine if a sequence of customer questions (Q) and support answers (A) follows valid rules.
         Each Q must be followed by at least one A, and all Q's must eventually be answered.
         The sequence must start with Q and maintain a valid balance where unanswered Qs never exceed A's at any point.

Algorithm:
  - Traverse the string from left to right.
  - Keep a running count of unanswered questions (rem).
  - For each 'Q': increment rem.
  - For each 'A': decrement rem.
  - If rem becomes negative at any point, it means we have more A's than Q's up to that point, violating the rule.
  - Reset rem to 0 if it goes negative to ensure we never consider negative unanswered questions.
  - At the end, if rem is 0, all questions were answered.

Time Complexity: O(n) where n is the length of the string, since we traverse once.
Space Complexity: O(1) as we use only a constant amount of extra space (variables rem, p, etc.).
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long rem(0);  // Tracks the number of unanswered questions at any point
    for (long p = 0; p < s.size(); p++) {
      rem += (s[p] == 'Q') - (s[p] == 'A');  // Increment for Q, decrement for A
      rem = (rem > 0) ? rem : 0;  // Ensure rem doesn't go below zero
    }
    std::cout << (rem <= 0 ? "yes" : "no") << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/