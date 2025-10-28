// Problem: CF 1527 B1 - Palindrome Game (easy version)
// https://codeforces.com/contest/1527/problem/B1

/*
 * Problem: B1. Palindrome Game (easy version)
 * Purpose: Determine the winner of a game where Alice and Bob take turns modifying a palindrome string of '0' and '1'.
 * Algorithm: Greedy + Game Theory
 *            - Count number of '0's in the string.
 *            - If there is exactly one '0', Alice wins (since she plays first and must change it, Bob gets 0 cost).
 *            - If the count of '0's is odd, Alice wins (because she will make the last move that turns all '0's to '1').
 *            - Otherwise, Bob wins.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) extra space (not counting input storage)
 */

#include <iostream>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0);
    for (long p = 0; p < s.size(); p++) {
      cnt += (s[p] == '0');  // Count the number of '0's in the string
    }
    if (cnt == 1) {
      std::cout << "BOB" << std::endl;  // Only one '0', Alice must play, Bob wins
    } else if (cnt % 2) {
      std::cout << "ALICE" << std::endl;  // Odd number of '0's, Alice plays last and wins
    } else {
      std::cout << "BOB" << std::endl;  // Even number of '0's, Bob plays last and wins
    }
  }
}


// https://github.com/VaHiX/codeForces/