// Problem: CF 1899 A - Game with Integers
// https://codeforces.com/contest/1899/problem/A

/*
Problem: Game with Integers
Algorithm: Mathematical game theory
Time Complexity: O(1) per test case
Space Complexity: O(1)

Vanya and Vova are playing a game where they start with integer n.
Vanya goes first and can either add 1 or subtract 1 on each turn.
If after Vanya's move the number becomes divisible by 3, Vanya wins.
If 10 moves pass without Vanya winning, Vova wins.
Both players play optimally.

Key insight: 
- If n % 3 == 0, Vanya loses immediately (Vova wins)
- If n % 3 != 0, Vanya can always make a move to make it divisible by 3 on his turn (Vanya wins)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    puts(x % 3 == 0 ? "Second" : "First"); // If n is divisible by 3, Vova wins; otherwise Vanya wins
  }
}


// https://github.com/VaHiX/codeForces/