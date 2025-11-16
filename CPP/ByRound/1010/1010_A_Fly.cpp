// Problem: CF 1010 A - Fly
// https://codeforces.com/contest/1010/problem/A

/*
 * Purpose: Calculate the minimum mass of fuel required for a rocket to travel
 *          from Earth to Mars and back, visiting n-2 intermediate planets.
 *          The rocket must have enough fuel to take-off and land at each planet,
 *          considering the efficiency of fuel use (a_i for take-off, b_i for landing).
 * 
 * Algorithm:
 * - The problem is solved using a mathematical approach.
 * - For each take-off or landing, we determine the fuel needed based on the
 *   mass to be lifted and the efficiency of the fuel.
 * - We simulate the flight from Earth to Mars and back using a loop that
 *   processes take-offs and landings.
 * - We use the formula derived from the physics of the problem: 
 *   for take-off: new_mass = old_mass * a_i / (a_i - 1)
 *   for landing: new_mass = old_mass * b_i / (b_i - 1)
 * 
 * Time Complexity: O(n) - We iterate through the planets twice (once for take-offs, once for landings),
 *                        each operation is constant time.
 * Space Complexity: O(1) - Only a few variables are used, constant space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long m;
  scanf("%ld", &m);
  double w = m;  // Initialize with payload mass
  for (long p = 0; p < 2 * n; p++) {
    long x;
    scanf("%ld", &x);  // Read the efficiency value for the current phase
    if (x == 1) {      // If efficiency is 1, no fuel can be used (division by zero)
      puts("-1");
      return 0;
    }
    w = w * x / (x - 1);  // Apply the fuel calculation formula
  }
  printf("%.8lf", w - m);  // Output the additional fuel needed (w - m)
  return 0;
}


// https://github.com/VaHiX/CodeForces/