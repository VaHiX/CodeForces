// Problem: CF 1537 D - Deleting Divisors
// https://codeforces.com/contest/1537/problem/D

/*
D. Deleting Divisors
Alice and Bob are playing a game. They start with a positive integer n and take alternating turns doing operations on it.
Each turn a player can subtract from n one of its divisors that isn't 1 or n.
The player who cannot make a move on his/her turn loses.
Alice always moves first.

Algorithm:
- If n is odd, Alice loses immediately since she cannot subtract any divisor (only even divisors exist for odd n, excluding 1 and itself).
- If n is even:
    - Count how many times we can divide n by 2 to make it odd.
    - If the resulting odd number > 1, Alice wins because there are more moves available.
    - Otherwise, if all factors of 2 are removed (n becomes 1):
        - If count of divisions by 2 is odd, Bob wins.
        - Else Alice wins.

Time Complexity: O(log n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) {            // If n is odd, Alice cannot make a move -> Bob wins
      puts("Bob");
      continue;
    }
    long cnt(0);            // Count how many times n can be divided by 2
    while (n % 2 == 0) {
      n /= 2;               // Divide n by 2
      ++cnt;                // Increment counter
    }
    if (n > 1) {            // If after removing all 2s, n > 1, Alice wins
      puts("Alice");
    } else if (cnt % 2) {   // If cnt is odd, Bob wins
      puts("Bob");
    } else {                // Else Alice wins
      puts("Alice");
    }
  }
}


// https://github.com/VaHiX/codeForces/