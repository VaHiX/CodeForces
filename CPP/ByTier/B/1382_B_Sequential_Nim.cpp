// Problem: CF 1382 B - Sequential Nim
// https://codeforces.com/contest/1382/problem/B

/*
B. Sequential Nim

Algorithm: This problem is a variant of the classic Nim game where moves are restricted to taking stones from the first non-empty pile. The key insight is that the game outcome depends on the parity (odd/even) of the number of piles with exactly 1 stone, after skipping all leading piles of size 1.

Approach:
- We simulate the process by counting how many piles (from left to right) have exactly 1 stone,
  but only after we've seen at least one pile with more than 1 stone.
- If there is any pile with more than 1 stone, then we track the count of 1-stone piles,
  and the final parity determines the winner.
- If all piles are size 1, the result is based on the total number of piles (odd/even).

Time Complexity: O(n) for each test case, where n is the number of piles.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ones(false), done(false); // 'ones' tracks parity of 1-stone piles, 'done' marks if we've seen pile > 1
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > 1) {            // If current pile has more than one stone
        done = true;          // Mark that we've encountered a pile with >1 stones
      } else if (!done) {     // If we haven't seen a pile > 1 yet and current pile is 1
        ones = 1 - ones;      // Toggle the count (parity)
      }
    }
    if (!done) {              // If we never saw a pile with > 1 stones
      ones = 1 - ones;        // Toggle one last time based on total number of piles being odd/even
    }
    puts(ones ? "Second" : "First"); // Output winner based on final parity
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/