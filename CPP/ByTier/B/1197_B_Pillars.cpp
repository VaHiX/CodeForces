// Problem: CF 1197 B - Pillars
// https://codeforces.com/contest/1197/problem/B

/*
B. Pillars
Algorithm: Greedy approach to check if the sequence can be transformed into a single stack
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks whether all disks can be moved onto one pillar, following rules:
- You can only move disks between adjacent pillars
- A disk can only be placed on top of a larger disk or an empty pillar
- The key insight is that if we can arrange the disks in a single stack, they must follow a pattern where there's at most one "change" from increasing to decreasing.

This solution checks:
1. If the sequence is non-decreasing (all increasing or flat), it's possible
2. If there's a decrease, the rest must remain non-increasing
3. If we ever go back up after a decrease, it's impossible

We use two flags:
- inc: tracks if we're currently in an increasing phase
- possible: tracks overall possibility of forming one stack

The algorithm simulates the movement by tracking if we are in an increasing or decreasing phase,
and ensures that once we transition to decreasing, we never go back up.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  bool inc(true), possible(true); // inc tracks increasing phase, possible tracks overall result
  long cur(-1); // cur tracks the last disk radius seen
  for (long p = 0; p < n; p++) { // iterate through each pillar
    long x;
    scanf("%ld", &x);
    if (inc && x < cur) { // if we were increasing but now decreasing
      inc = false; // switch to decreasing mode
    } else if (!inc && x > cur) { // if we're in decreasing mode and now increasing
      possible = false; // impossible to form one stack
      break;
    }
    cur = x; // update current disk radius
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/