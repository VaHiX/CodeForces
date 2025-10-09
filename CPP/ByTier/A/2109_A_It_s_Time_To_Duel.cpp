// Problem: CF 2109 A - It's Time To Duel
// https://codeforces.com/contest/2109/problem/A

/*
 * Problem: A. It's Time To Duel
 * Purpose: Determine if at least one player is lying about their duel results in a tournament.
 * 
 * Algorithm/Techniques:
 * - Simulation approach to check consistency of reports.
 * - For each test case, we simulate the duel outcomes and validate:
 *   1. No two consecutive players both report 0 (since at least one must win).
 *   2. The total number of reported wins (sum of array) is less than n (total number of duels).
 * 
 * Time Complexity: O(n) per test case, where n is the number of players.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool liar(false);                    // Flag to indicate if a liar is found
    long cnt(0), prev(1);                // cnt counts total wins, prev tracks previous player's report
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (!prev && !x) {                 // If both current and previous player report 0, contradiction
        liar = true;
      }
      prev = x;                          // Store current player's report for next iteration
      cnt += x;                          // Accumulate total wins reported
    }
    if (cnt >= n) {                      // If total reports >= number of players, impossible
      liar = true;
    }
    puts(liar ? "YES" : "NO");           // Output result
  }
}


// https://github.com/VaHiX/codeForces/