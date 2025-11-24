// Problem: CF 1877 A - Goals of Victory
// https://codeforces.com/contest/1877/problem/A

/*
 * Problem: Determine the efficiency of the missing team in a football tournament.
 *
 * Algorithm:
 * - Each team plays every other team exactly once (n teams => n*(n-1)/2 matches).
 * - For each match, we get two goal counts (for each team).
 * - Efficiency of a team = sum of goals scored by that team - sum of goals scored by opponents.
 * - Given efficiencies of (n-1) teams, the efficiency of the missing team can be derived from:
 *   Let S = sum of given efficiencies. The total sum of all team efficiencies equals zero
 *   because each goal scored contributes +1 to a team's efficiency and -1 to opponent's.
 *   Therefore, efficiency of missing team = -S.
 *
 * Time Complexity: O(n) per test case — linear scan of n-1 elements.
 * Space Complexity: O(1) — only using constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cs(0);  // cumulative sum of given efficiencies
    for (long p = 1; p < n; p++) {  // loop through all but one team's efficiency
      long x;
      scanf("%ld", &x);
      cs += x;  // accumulate the given efficiencies
    }
    printf("%ld\n", -cs);  // the missing team's efficiency is the negative of sum
  }
}


// https://github.com/VaHiX/codeForces/