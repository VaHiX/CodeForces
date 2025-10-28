// Problem: CF 1673 A - Subtle Substring Subtraction
// https://codeforces.com/contest/1673/problem/A

/* 
 * Problem: A. Subtle Substring Subtraction
 * Algorithm: Game Theory + Greedy Strategy
 * Time Complexity: O(n) where n is the length of the string s
 * Space Complexity: O(1)
 *
 * The game involves two players, Alice and Bob, who alternately remove substrings 
 * from a given string. Alice can only remove even-length substrings, Bob can only 
 * remove odd-length substrings. Each player tries to maximize their own score.
 * 
 * Key insight:
 * - If the string has an odd length, Alice plays first and removes everything except
 *   the last character (which Bob then takes), so Alice gets the sum of all characters
 *   except the last one, Bob gets just the last character's value.
 * - If the string has an even length, Alice can take the best possible strategy by
 *   removing half the string from the start or end to maximize her own score, while 
 *   minimizing Bob's gain. 
 *
 * In the code:
 * - v accumulates total value of all characters in the string.
 * - mn is the minimum value between first and last character.
 * - The difference is calculated based on parity of string and optimal play.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long v(0);
    for (long p = 0; p < s.size(); p++) {
      v += (s[p] - 'a' + 1); // Accumulate total character values
    }
    long mn = ((s[0] < s.back()) ? s[0] : s.back()) - 'a' + 1; // Minimum first/last char value
    if (s.size() == 1) {
      std::cout << "Bob " << mn << std::endl; // If only one character, Bob gets it
    } else {
      std::cout << "Alice " << (v - 2 * mn * (s.size() % 2)) << std::endl;
      // Alice's score = total - 2*min*(1 if odd length else 0)
    }
  }
}


// https://github.com/VaHiX/codeForces/