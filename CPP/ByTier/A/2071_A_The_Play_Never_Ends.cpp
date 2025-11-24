// Problem: CF 2071 A - The Play Never Ends
// https://codeforces.com/contest/2071/problem/A

/*
 * Problem: A. The Play Never Ends
 * Algorithm/Techniques: Mathematical pattern recognition
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * Players Sosai, Fofo, and Hohai play table tennis in an infinite loop.
 * In each match, two players compete, one spectates.
 * The rules ensure no player plays three times consecutively.
 * We are to determine if the spectator of the first match can also be the spectator in the k-th match.
 *
 * Pattern Analysis:
 * - If k == 1: YES (trivial case)
 * - If k % 3 == 0: NO (because after every 3 matches, each player gets a turn to sit out,
 *   and for k divisible by 3, the spectator must have played in previous two matches)
 * - Otherwise: YES
 *
 * The key insight is that only when k is divisible by 3 does the first spectator not return.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    // If (k - 1) is NOT divisible by 3, then first spectator can be spectator again
    puts((k - 1) % 3 ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/