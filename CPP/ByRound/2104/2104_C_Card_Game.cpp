// Problem: CF 2104 C - Card Game
// https://codeforces.com/contest/2104/problem/C

/*
C. Card Game

Purpose:
This code determines the winner of a card game played between Alice and Bob, given the initial distribution of cards.
The game follows specific rules where cards beat others in a circular manner (card i beats j if i > j, except card 1 beats card n).
Both players play optimally, and we output the name of the winner.

Algorithms/Techniques:
- Simulation with strategic checks based on first and last card ownership.
- Greedy-like optimal play decision logic applied to sub-cases.

Time Complexity: O(n) per test case, where n is the number of cards.
Space Complexity: O(1), only using a fixed amount of extra space regardless of input size.

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
    if (s[0] == s.back()) {  // If first and last card are owned by the same player
      // That player wins immediately because they can always beat the opponent's card
      std::cout << (s[0] == 'A' ? "Alice" : "Bob") << std::endl;
    } else if (s[0] == 'A') {  // If Alice starts with an A
      // Check if Alice has a winning strategy depending on the middle part of the string
      bool alice(true);
      for (int p = n - 2; alice && p >= 0; p--) {
        if (s[p] == 'B') {
          alice = false;  // Bob blocks Alice's potential winning path
        }
      }
      std::cout << (alice ? "Alice" : "Bob") << std::endl;
    } else {  // If Bob starts with a B
      // Check if Bob can make a move that leads to his victory
      std::cout << (s[n - 2] == 'A' ? "Alice" : "Bob") << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/