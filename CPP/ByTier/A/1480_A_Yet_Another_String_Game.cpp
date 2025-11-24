// Problem: CF 1480 A - Yet Another String Game
// https://codeforces.com/contest/1480/problem/A

#include <iostream>
#include <string>

/*
 * Problem: A. Yet Another String Game
 * Purpose: Given a string, simulate optimal play between Alice and Bob where:
 *          - Alice wants the lexicographically smallest result.
 *          - Bob wants the lexicographically largest result.
 *          - Players alternate turns starting with Alice.
 *          - Each player can change any character to another character not equal to current.
 *
 * Algorithm/Technique: Greedy simulation
 *
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) extra space (excluding input/output).
 */
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    for (long p = 0; p < s.size(); p++) {
      if (p % 2) {
        // Bob's turn: make the character as large as possible (maximize lexicographically)
        s[p] = (s[p] != 'z' ? 'z' : 'y');
      } else {
        // Alice's turn: make the character as small as possible (minimize lexicographically)
        s[p] = (s[p] != 'a' ? 'a' : 'b');
      }
    }
    std::cout << s << std::endl;
  }
}

// https://github.com/VaHiX/codeForces/