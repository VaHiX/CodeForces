// Problem: CF 451 C - Predict Outcome of the Game
// https://codeforces.com/contest/451/problem/C

/*
C. Predict Outcome of the Game
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem involves determining whether it's possible to arrange the outcomes of a football tournament
such that no team ends up with more wins than any other team, given:
- n total games
- k already played games
- d1 = |wins(team1) - wins(team2)| from the friend's guess
- d2 = |wins(team2) - wins(team3)| from the friend's guess

The approach uses mathematical analysis:
1. For a balanced tournament, each team must have n/3 wins at the end.
2. We derive constraints based on different possible assignments of wins to teams.
3. Each constraint checks divisibility conditions modulo 3 to validate valid combinations.

For k=0, we just check if n is divisible by 3 (no games played yet).
Otherwise, we try all valid combinations of d1 and d2 assignments using algebraic constraints derived from:
- Total wins must be n
- Constraints on absolute differences d1 and d2 must hold
*/

#include <cstdio>
int main() {
  long T;
  scanf("%ld\n", &T);
  while (T--) {
    long long n, k, d1, d2;
    scanf("%lld %lld %lld %lld\n", &n, &k, &d1, &d2);
    if (n % 3 != 0) {  // If total games don't divide evenly among three teams
      puts("no");
      continue;
    }
    bool possible = 0;
    // Check case 1: d1 = |a - b| and d2 = |b - c| where (a, b, c) are relative wins
    if ((d1 + 2 * d2 <= k) && ((k - d1 - 2 * d2) % 3 == 0) &&
        (2 * d1 + d2 <= n - k) && ((n - k - 2 * d1 - d2) % 3 == 0)) {
      possible = 1;
    }
    // Check case 2: different assignment of d1 and d2 with symmetry
    if ((d1 <= d2) && (d1 + d2 <= k) && ((k - d1 - d2) % 3 == 0) &&
        (2 * d2 - d1 <= n - k) && ((n - k - 2 * d2 + d1) % 3 == 0)) {
      possible = 1;
    }
    // Check case 3: symmetric to above
    if ((d2 <= d1) && (d1 + d2 <= k) && ((k - d1 - d2) % 3 == 0) &&
        (2 * d1 - d2 <= n - k) && ((n - k - 2 * d1 + d2) % 3 == 0)) {
      possible = 1;
    }
    // Check case 4: yet another assignment
    if ((2 * d1 + d2 <= k) && ((k - 2 * d1 - d2) % 3 == 0) &&
        (d1 + 2 * d2 <= n - k) && ((n - k - d1 - 2 * d2) % 3 == 0)) {
      possible = 1;
    }
    // Check case 5: another symmetric condition
    if ((d1 <= d2) && (2 * d2 - d1 <= k) && ((k - 2 * d2 + d1) % 3 == 0) &&
        (d1 + d2 <= n - k) && ((n - k - d1 - d2) % 3 == 0)) {
      possible = 1;
    }
    // Check case 6: symmetric to last one
    if ((d2 <= d1) && (2 * d1 - d2 <= k) && ((k - 2 * d1 + d2) % 3 == 0) &&
        (d1 + d2 <= n - k) && ((n - k - d1 - d2) % 3 == 0)) {
      possible = 1;
    }
    if (possible) {
      puts("yes");
    } else {
      puts("no");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/