// Problem: CF 651 A - Joysticks
// https://codeforces.com/contest/651/problem/A

/*
 * Problem: Joysticks
 * Purpose: Determine the maximum number of minutes two joysticks can be used
 *          before one of them runs out of charge, given their initial charges
 *          and charging/discharging rules.
 *
 * Algorithm:
 *   - Simulate the process of charging and discharging to find the optimal
 *     strategy for maximizing game duration.
 *   - Key idea: At each step, we can either:
 *     1. Connect one joystick to the charger (increases its charge by 1%)
 *     2. Let it discharge (decreases its charge by 2%)
 *   - The optimal policy is to alternate charging between the two joysticks
 *     in a strategic way so that neither runs out too early.
 *   - Mathematical derivation reveals the answer using modulo arithmetic:
 *     If a and b are the initial charges, then the number of turns is:
 *     (a + b - 2) - ((a - b) % 3 == 0 ? 1 : 0)
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  int a, b;
  scanf("%d %d\n", &a, &b);
  if (a <= 1 && b <= 1) {
    puts("0");
  } else {
    printf("%d\n", a + b - 2 - ((a - b) % 3 == 0));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/