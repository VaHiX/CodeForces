// Problem: CF 1872 B - The Corridor or There and Back Again
// https://codeforces.com/contest/1872/problem/B

/*
B. The Corridor or There and Back Again
Algorithms/Techniques: Greedy algorithm
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem requires finding the maximum value of k such that one can travel from room 1 to room k and back to room 1 safely,
avoiding all traps. Each trap is located in a specific room and activates after a certain number of seconds after entering.
To avoid a trap, the path must not enter a room with an active trap.

Approach:
- For each test case, iterate through all traps to compute the latest possible room (k) that can be reached
  before any trap becomes active.
- The key insight is that to safely go from room 1 to room k and return, we must ensure that by time 
  (k + 1), no trap in room d_i becomes active. This means we should not enter that room at or after 
  time (s_i - 1) since the trap activates s_i seconds after entering.
- The safe condition for a trap is: d_i + (s_i - 1) / 2 < k, which implies that it's possible to reach 
  k before any trap becomes active.
- The maximum valid k can be found by computing the minimum among all such limits.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(1e9 + 7); // Initialize result to a large value
    for (long p = 0; p < n; p++) {
      long d, s;
      scanf("%ld %ld", &d, &s);
      long lim = d + (s - 1) / 2; // Compute the limiting room number
      res = (res < lim) ? res : lim; // Keep the minimum of all limits
    }
    printf("%ld\n", res); // Output the maximum k that is safe to reach
  }
}


// https://github.com/VaHiX/codeForces/