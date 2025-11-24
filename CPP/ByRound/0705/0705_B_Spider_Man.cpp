// Problem: CF 705 B - Spider Man
// https://codeforces.com/contest/705/problem/B

/*
B. Spider Man
Algorithms/Techniques: Game theory, Nim-like strategy based on XOR (Nim-sum) of cycle lengths.
Time Complexity: O(n), where n is the number of tests.
Space Complexity: O(1), only using a few variables for computation.

The game is about reducing cycles into smaller ones. Each move splits a cycle of size x >= 2 into two cycles of sizes p and (x - p) where 1 <= p < x.
This is a classic Nim-like game. A key insight is that the only meaningful cycles are those with size > 1,
as cycles of size 1 do not allow any moves. The winning condition depends on whether the XOR (Nim-sum) of all cycle sizes (excluding 1s) is zero or not.
If the Nim-sum is zero at the start, the first player loses; otherwise, the first player wins.
In this implementation, we simulate the process by tracking the cumulative parity of moves,
which effectively computes the Nim-sum (since XOR with 1 toggles parity).
*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  long mod(0);  // This variable tracks cumulative xor-like behavior (parity of nim-sum)
  while (n--) {
    long a;
    scanf("%ld", &a);
    mod += (a - 1);  // Simulates adding to the Nim-sum; subtracting 1 because cycles of size 1 are irrelevant
    mod %= 2;        // Keep track of parity (as if computing XOR)
    puts((mod > 0) ? "1" : "2");  // Output winner: 1 for first player, 2 for second
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/