// Problem: CF 1841 A - Game with Board
// https://codeforces.com/contest/1841/problem/A

/*
Problem: Game with Board
Algorithms/Techniques: Game Theory, Optimal Play Analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

Alice and Bob play a game where they start with n integers all equal to 1 on a board.
On each turn, a player must choose at least two equal integers, erase them, and write their sum.
The player who cannot make a move (all numbers are distinct) wins.
This problem is solved by realizing that:
- If n < 5, Alice loses because no matter what she does, Bob can always win.
- If n >= 5, Alice can always win by making an optimal first move.

The solution simply checks if n < 5.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long n;
    scanf("%ld", &n); // Read the initial number of 1s on the board
    puts(n < 5 ? "Bob" : "Alice"); // Output winner based on the condition
  }
}


// https://github.com/VaHiX/codeForces/