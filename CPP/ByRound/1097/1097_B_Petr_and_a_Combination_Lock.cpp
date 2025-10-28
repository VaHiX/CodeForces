// Problem: CF 1097 B - Petr and a Combination Lock
// https://codeforces.com/contest/1097/problem/B

/*
B. Petr and a Combination Lock
Purpose: Determine if there exists a combination of clockwise/counterclockwise rotations 
         such that the sum of all rotations (with signs) is a multiple of 360 degrees.
         This problem uses dynamic programming to track all possible angular sums.

Algorithms/Techniques:
- Dynamic Programming on states representing reachable angles
- For each rotation, we can either add or subtract its value to current angle
- State transition: p[i][j] = number of ways to reach angle j after i rotations

Time Complexity: O(n * 360) = O(n), since n <= 15 and 360 is constant
Space Complexity: O(16 * 360) = O(1) due to fixed dimensions

Input: n rotations, each with degree value
Output: YES if a valid combination exists, NO otherwise
*/

#include <stdio.h>

int i, j, k, n, p[16][360]; // p[i][j] = number of ways to reach angle j after i steps

int main() {
  p[0][0] = 1; // Base case: 0 rotations -> 0 degree (1 way)

  for (scanf("%d", &n); i++ < n;) { // For each rotation from 1 to n
    for (j = !scanf("%d", &k); j < 360; j++) // For all possible angles
      p[i][(j + k) % 360] += p[i - 1][j],       // Add k degrees clockwise
          p[i][(j - k + 360) % 360] += p[i - 1][j]; // Subtract k degrees counterclockwise
  }

  puts(p[n][0] ? "YES" : "NO"); // If there's at least one way to reach 0 degrees
}


// https://github.com/VaHiX/codeForces/