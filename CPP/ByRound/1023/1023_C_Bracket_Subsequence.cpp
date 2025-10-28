// Problem: CF 1023 C - Bracket Subsequence
// https://codeforces.com/contest/1023/problem/C

/*
C. Bracket Subsequence
Algorithm: Greedy approach to construct a valid bracket subsequence of length k.
We use a greedy strategy:
1. First, we select the first k/2 opening brackets '(' and add them to result.
2. Then, we match each closing bracket ')' with an unmatched opening bracket.

Time Complexity: O(n) - single pass through the string
Space Complexity: O(k) - output string of length k

Techniques:
- Greedy selection of brackets
- Tracking unmatched opening brackets
*/

#include <iostream>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  long w(k / 2), rem(0);           // w: remaining opening brackets to pick, rem: unmatched opening brackets
  std::string t("");               // t: result subsequence
  for (long p = 0; p < s.size(); p++) {
    if (w > 0 && s[p] == '(') {    // if we still need opening brackets and current char is '('
      t += '(';
      --w;                         // decrement count of needed opening brackets
      ++rem;                       // increment unmatched opening bracket counter
    } else if (rem > 0 && s[p] == ')') {  // if we have unmatched opening and current char is ')'
      t += ')';
      --rem;                       // decrement unmatched opening bracket counter
    }
  }
  std::cout << t << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/