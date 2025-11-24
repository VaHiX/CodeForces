// Problem: CF 1733 B - Rule of League
// https://codeforces.com/contest/1733/problem/B

/*
Algorithm/Techniques: Simulation, Greedy, Mathematical Analysis

Time Complexity: O(n) per test case, where n is the number of players.
Space Complexity: O(1) - only using a few variables for computation, no extra space used.

This problem simulates a single-elimination badminton tournament where each game is between the current winner and the next player in order.
The goal is to determine if there's a valid tournament outcome such that some players have won exactly x games and others exactly y games.

Approach:
1. Analyze the constraints:
   - Only one of x or y can be zero (because if both are zero, no one wins any games, which is impossible).
   - If one of them is zero, then the other must be such that (n-1) is divisible by that value (number of games total).
2. Based on the values of x and y:
   - If both are non-zero, impossible.
   - If one is zero and the other is not, we must check divisibility condition.
   - If that condition holds, we simulate the tournament by assigning players to win in a pattern to satisfy the win counts.

The simulation works by:
- First determining which player wins how many games based on the input values.
- Then, placing that pattern in a way that the tournament progresses logically.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x, y;
    scanf("%ld %ld %ld", &n, &x, &y);
    long u = (x < y) ? x : y;
    long v = (x > y) ? x : y;
    if (u == 0 && v == 0) {
      puts("-1");
    } else if (u > 0 && v > 0) {
      puts("-1");
    } else if (u == 0 && (n - 1) % v) {
      puts("-1");
    } else if (u == 0 && ((n - 1) % v == 0)) {
      long cur(0);
      for (long p = 0; p < n - 1; p++) {
        if (p % v == 0) {
          cur = 2 + p;  // Determine the winner of the game at position p
        }
        printf("%ld ", cur);
      }
      puts("");
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/CodeForces/