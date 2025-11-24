// Problem: CF 1153 A - Serval and Bus
// https://codeforces.com/contest/1153/problem/A

/*
 * Problem: A. Serval and Bus
 * Purpose: Determine which bus route Serval will take when he arrives at the station at time t.
 *          If multiple buses arrive at the same time, any one can be chosen.
 *
 * Algorithm:
 *   - For each bus route, compute the earliest bus that arrives at or after time t.
 *   - This is done by checking if the first bus (s_i) is after time t,
 *     otherwise calculate when the next bus after time t arrives using modular arithmetic.
 *   - Return the route number with the minimum waiting time.
 *
 * Time Complexity: O(n), where n is the number of bus routes.
 * Space Complexity: O(1), only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  long n, t;
  scanf("%ld %ld", &n, &t);
  long ans(n + 1), mn(1e6); // ans stores route number, mn stores minimum waiting time
  for (long p = 1; p <= n; p++) {
    long s, d;
    scanf("%ld %ld", &s, &d);
    long w;
    if (s > t) {
      // If first bus is already after time t, wait time is s - t
      w = s - t;
    } else {
      // Otherwise, find the next bus that arrives at or after time t
      // ((t - s + d - 1) / d) computes how many intervals we need to pass
      // Add that to s and subtract t to get wait time
      w = s + d * ((t - s + d - 1) / d) - t;
    }
    if (w < mn) {
      ans = p;   // Update answer route number
      mn = w;    // Update minimum wait time
    }
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/