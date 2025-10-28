// Problem: CF 1972 B - Coin Games
// https://codeforces.com/contest/1972/problem/B

/*
B. Coin Games
Algorithm/Technique: Game Theory, Simulation with Bit Manipulation
Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input storage)

This problem models a game where players take turns removing and flipping coins in a circle.
The key insight is that we can model the game state using a single boolean variable,
representing whether the number of 'U' coins is odd or even. 
Each move flips two adjacent coins, so the parity (odd/even) of 'U's determines
the outcome based on the total number of moves required to finish the game.

The code simulates how many times 'U' appears in a sequence, and alternates the result 
based on an odd/even count of moves. If 'U' count leads to even number of operations,
Alice wins; otherwise Bob wins.
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
    bool a(false); // Tracks the parity of number of 'U's encountered so far
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'U') {
        a = !a; // Toggle the boolean value: flips the parity
      }
    }
    std::cout << (a ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/