// Problem: CF 1194 D - 1-2-K Game
// https://codeforces.com/contest/1194/problem/D

/*
D. 1-2-K Game
Algorithm: Game theory with dynamic programming optimization using modular arithmetic.
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem is a classic game theory problem that can be solved using the Sprague-Grundy theorem
or by observing periodic patterns in winning/losing positions.

The key insight is to determine if a position is winning or losing for the current player.
When k is not divisible by 3:
- If n % 3 != 0, Alice wins (Alice is in a winning position).
- Otherwise, Bob wins.

When k is divisible by 3:
- We compute m = n % (k + 1)
- If (m % 3) != 0 OR m == k, then Alice wins.
- Otherwise, Bob wins.

This is based on the periodic nature of positions modulo (k+1), where the game repeats every k+1 steps.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k % 3) { // When k is not divisible by 3
      puts(n % 3 ? "Alice" : "Bob"); // If n % 3 != 0, Alice wins; else Bob wins
    } else {
      long m = n % (k + 1); // Compute the remainder when dividing by (k+1)
      puts(((m % 3) || (m == k)) ? "Alice" : "Bob"); // Check winning condition for this case
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/