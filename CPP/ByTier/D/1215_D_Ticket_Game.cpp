// Problem: CF 1215 D - Ticket Game
// https://codeforces.com/contest/1215/problem/D

/* 
 * Problem: D. Ticket Game
 * Algorithm/Techniques: Greedy, Game Theory, Mathematical Analysis
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Description:
 * Two players (Monocarp and Bicarp) play a game on a ticket with n digits (n is even).
 * Some digits are erased ('?') and need to be filled optimally.
 * The goal is to determine if the resulting ticket will have equal sums of first and second halves.
 * Monocarp plays first and wants the ticket to be unhappy, Bicarp wants it happy.
 * Both play optimally.
 * 
 * Approach:
 * 1. Calculate difference between sums of two halves considering '?' as contributing to either side.
 * 2. For each '?', decide its contribution based on position: 
 *    - First half (2*p < n): contributes -1 if it's a '?'
 *    - Second half (2*p >= n): contributes +1 if it's a '?'
 * 3. Count total imbalance (imb) from '?' characters.
 * 4. For optimal play, we check whether current difference can be balanced to zero,
 *    using the fact that in even number of '?', Bicarp can always ensure a draw or win.
 *    The condition checks if diff + 9*imb/2 == 0 (where 9 is max possible value difference per '?')
 */
#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long diff(0), imb(0); // diff: difference between sums; imb: imbalance from '?'
  for (long p = 0; p < s.size(); p++) {
    int sgn = (2 * p < n) ? -1 : 1; // sign determines which half the position belongs to
    if (s[p] == '?') {
      imb += sgn; // accumulate imbalance based on half
    } else {
      diff += (s[p] - '0') * sgn; // add digit value with appropriate sign
    }
  }
  puts((diff + 9 * imb / 2 == 0) ? "Bicarp" : "Monocarp"); // determine winner based on final balance
  return 0;
}


// https://github.com/VaHiX/codeForces/