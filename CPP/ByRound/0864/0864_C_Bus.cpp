// Problem: CF 864 C - Bus
// https://codeforces.com/contest/864/problem/C

/*
Algorithm: Greedy Simulation
Approach:
- Simulate the bus journeys from 0 to a and back to 0.
- For each journey, determine if refueling is needed at point f.
- Refuel only when necessary (greedily): when the current fuel is not enough to complete the journey or the next segment.
- Keep track of remaining fuel and refuel count.
- Check feasibility at each step.

Time Complexity: O(k) - Single pass through k journeys
Space Complexity: O(1) - Only using a few variables for tracking

*/
#include <cstdio>
int main() {
  long a, b, f, k;
  scanf("%ld %ld %ld %ld", &a, &b, &f, &k);
  // Early exit: if initial fuel is not enough to reach the gas station
  if (b < f || b < a - f) {
    puts("-1");
    return 0;
  }
  long g(b), count(0);  // g is current fuel, count is number of refuels
  for (long p = 1; p <= k; p++) {
    if (p & 1) {  // Odd journey: 0 -> a
      // Travel from 0 to f (f units)
      g -= f;
      if (g < 0) {
        puts("-1");
        return 0;
      }
      // Check if refuel needed before proceeding to a
      // For next journey (if exists), it will be from a to 0, so need 2*(a-f) extra fuel
      // If this is last journey, just need (a-f) fuel to reach the end point
      if (g < (p < k ? 2 : 1) * (a - f)) {
        g = b;
        ++count;
      }
      // Travel from f to a (a-f units)
      g -= (a - f);
      if (g < 0) {
        puts("-1");
        return 0;
      }
    } else {  // Even journey: a -> 0
      // Travel from a to f (a-f units)
      g -= (a - f);
      if (g < 0) {
        puts("-1");
        return 0;
      }
      // Check if refuel needed before proceeding to 0
      // For next journey (if exists), it will be from 0 to a, so need 2*f extra fuel
      // If this is last journey, just need f fuel to reach the end point
      if (g < (p < k ? 2 : 1) * f) {
        g = b;
        ++count;
      }
      // Travel from f to 0 (f units)
      g -= f;
      if (g < 0) {
        puts("-1");
        return 0;
      }
    }
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/