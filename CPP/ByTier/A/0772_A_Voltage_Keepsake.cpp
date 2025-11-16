// Problem: CF 772 A - Voltage Keepsake
// https://codeforces.com/contest/772/problem/A

/*
 * Problem: Voltage Keepsake
 * Algorithm: Binary Search on Answer
 * Time Complexity: O(n * log(max_time)) where max_time is around 1e18
 * Space Complexity: O(1) - only using a few variables and fixed size arrays
 *
 * The problem is about determining the maximum time we can use n devices
 * simultaneously, given their power consumption rates and initial power,
 * with one charger that provides p units of power per second.
 * 
 * We use binary search on the answer. For a given time t, we check whether 
 * it's possible to sustain all devices for that long. To do this, we simulate
 * charging optimally: charge the device that will last the shortest time 
 * (in terms of remaining power) first.
 *
 * Key steps:
 * 1. If total consumption <= charger power, we can use devices indefinitely.
 * 2. Binary search over time:
 *    - For a given time t, calculate how much power we can save by optimally
 *      charging devices.
 *    - If we can save enough power, then t is feasible.
 *    - Otherwise, it's not feasible.
 *
 * The precision of binary search is controlled by a threshold (1e-7).
 */

#include <cstdio>
const int N = 100005;
long long s; // Total power consumption of all devices
int n, p, a[N], b[N], i; // a[i]: power consumption, b[i]: initial power
double l, m, r, x, y, t; // l: lower bound, m: mid, r: upper bound, x: available charged power

int main() {
  scanf("%d%d", &n, &p);
  for (i = 1; i <= n; ++i)
    scanf("%d%d", a + i, b + i), s += a[i]; // Read input and accumulate total consumption
  if (s <= p) // If total consumption is less than or equal to charger power
    return puts("-1"), 0; // We can use devices indefinitely
  l = 0;
  r = 1e18; // Upper bound set to large value for binary search
  for (; r - l > 1e-7;) { // Binary search loop with tolerance for floating point
    m = (l + r) / 2; // Midpoint of the current search range
    x = m * p; // Total power that can be added by charger in time m
    for (i = 1; i <= n; ++i) { // Try all devices to calculate how much we can save
      t = b[i] * 1.0 / a[i]; // Time this device can last without charging
      if (t < m) // If device would run out before time m
        x -= (m - t) * a[i]; // Subtract the power needed to keep it going
      if (x < 0) // If we don't have enough charger power
        break; // Not feasible for this time m
    }
    if (i > n) // If all devices were processed successfully
      l = m; // Time m is feasible, try higher values
    else
      r = m; // Time m is not feasible, try lower values
  }
  printf("%.5f\n", l); // Print the maximum feasible time
  return 0;
}


// https://github.com/VaHiX/CodeForces/