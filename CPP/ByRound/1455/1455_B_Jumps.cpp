// Problem: CF 1455 B - Jumps
// https://codeforces.com/contest/1455/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    long step(1), total(0);
    // Accumulate steps until we overshoot or reach the target
    while (total < x) {
      total += step;
      ++step;
    }
    // If we overshot by exactly 1, we need to adjust our last step
    if (total != x + 1) {
      --step;
    }
    printf("%ld\n", step);
  }
}
/*
B. Jumps

Purpose: 
This program computes the minimum number of jumps required to reach a given point `x` on the number line starting from 0. Each jump `k` (starting from 1) allows moving either `+k` or `-1` units from current position.

Algorithm:
- For each test case, simulate the process of accumulating jump distances until reaching or overshooting `x`.
- Adjust final step count if overshoot is exactly by one unit (due to the structure of optimal path).

Time Complexity: O(sqrt(x)) per test case, since we simulate up to roughly sqrt(2*x) steps.
Space Complexity: O(1), only using a few integer variables.

Techniques:
- Greedy simulation with careful adjustment for overshoot cases.
*/

// https://github.com/VaHiX/codeForces/