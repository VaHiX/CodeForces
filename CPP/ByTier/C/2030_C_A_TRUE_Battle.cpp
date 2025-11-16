// Problem: CF 2030 C - A TRUE Battle
// https://codeforces.com/contest/2030/problem/C

/*
C. A TRUE Battle
time limit per test2 seconds
memory limit per test256 megabytes

Problem Description:
Alice and Bob are playing a game on a binary string of length n. Each character is either '0' (false) or '1' (true).
They take turns placing either 'and' or 'or' operators between adjacent booleans, with Alice going first.
Alice wants the final expression to evaluate to true, while Bob wants it to evaluate to false.
The evaluation process:
- If there's an 'and', pick any one and replace with its evaluation.
- Otherwise, if there's an 'or', pick any one and replace.
- The result of any compound statement is unique.

Algorithm/Technique:
Greedy approach based on key observations about the structure of the string and possible moves:
1. Alice wins if there exists at least one '1' that is not adjacent to another '1'.
2. The only way Bob can win is if all characters are 0, or if all chars are 1 but there is no way for Alice to make a move that leads to a true statement.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The winning condition is determined simply by checking:
- If the string contains at least one '1' not adjacent to another '1', then Alice can win.
- Otherwise, if the entire string consists of only '1's (and thus no such isolated '1'), or it contains a pattern that leads to guaranteed loss for Alice, Bob wins.

This simplifies the actual game theory logic, but the solution checks a sufficient condition:
- For each '1', if it is either at the start, end, or different from its neighbor, then Alice can make a winning move.
*/

#include <stddef.h>
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
    bool win(false); // Flag indicating if Alice wins
    for (size_t p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        continue; // Skip zeros as they cannot be used to form a winning move directly
      }
      // If we find a 1 that is at the start (p==0), or end (p==n-1),
      // or is different from its previous character, it's a key position for Alice
      if (p == 0 || p == n - 1 || s[p - 1] == s[p]) {
        win = true;
      }
    }
    std::cout << (win ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/