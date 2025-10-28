// Problem: CF 1901 B - Chip and Ribbon
// https://codeforces.com/contest/1901/problem/B

/*
Problem: Chip and Ribbon
Algorithm: Greedy approach with difference tracking
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves placing a chip on a ribbon of n cells and incrementing values in cells 
while minimizing the number of teleports. The key insight is that we can move the chip 
sequentially, but if the required count in a cell drops, we must teleport.

We simulate the process by tracking how much "extra" work (in terms of increments) we need 
to do due to going back or skipping cells. For each step, the difference between current
and previous target values determines how many extra teleports may be needed.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(0);              // Previous target count
    scanf("%ld", &prev);
    long long ans(prev - 1);   // First cell must be incremented to 'prev', so we start with 'prev - 1' increments elsewhere
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      long diff = x - prev;    // Difference between current and previous target counts
      diff = (diff > 0) ? diff : 0;  // Only consider positive differences (i.e., when we need to go forward)
      ans += diff;             // Add this difference to our total teleport count
      prev = x;                // Update previous target count
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/