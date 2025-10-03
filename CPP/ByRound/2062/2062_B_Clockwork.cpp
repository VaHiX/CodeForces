// Problem: CF 2062 B - Clockwork
// https://codeforces.com/contest/2062/problem/B

/*
B. Clockwork

Purpose:
This program determines whether it's possible to continue the process indefinitely on a line of n time clocks,
where each clock decreases by 1 every second, and movement/resetting rules apply. The key insight is that for
each position i, we must ensure that we can reach it in time before its value becomes 0.

Algorithm:
- For each test case, consider each index i in the array.
- Calculate the maximum distance from i to either end of the array, which determines how many seconds 
  we have to reach and reset that clock without losing.
- If at any point a[i] <= 2 * max distance from that position to ends, it's impossible to avoid losing.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/

#include <algorithm>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool possible(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Calculate the maximum distance from current position to either end
      long dist = 2 * std::max(p, n - 1 - p);
      // If the time at this position is less than or equal to twice the max distance,
      // it's impossible to avoid losing (we can't reach and reset in time)
      if (x <= dist) {
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/