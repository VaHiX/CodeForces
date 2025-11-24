// Problem: CF 894 A - QAQ
// https://codeforces.com/contest/894/problem/A

/*
Purpose: Count the number of subsequences "QAQ" in a given string of uppercase English letters.

Algorithm/Techniques: 
  - Single-pass linear scan of the string.
  - Use counters to track:
    * q: number of 'Q' characters seen so far.
    * qa: number of "QA" subsequences ending at current position.
    * qaq: total number of "QAQ" subsequences found.
  - For each 'A': increment qa by the number of 'Q's seen so far (since each 'Q' can form a "QA" with this 'A').
  - For each 'Q': increment q and qaq by the current qa value (each previous "QA" can now form a "QAQ").

Time Complexity: O(n) where n is the length of the input string.
Space Complexity: O(1) as only a constant amount of extra space is used.
*/

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long q(0), qa(0), qaq(0);
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == 'A') {
      qa += q;  // Each 'Q' before this 'A' can form a "QA" with current 'A'
    } else if (s[p] == 'Q') {
      ++q;      // Increment count of 'Q's
      qaq += qa; // Each existing "QA" can now form a "QAQ" with this 'Q'
    }
  }
  std::cout << qaq << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/