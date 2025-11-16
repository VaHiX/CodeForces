// Problem: CF 1097 B - Petr and a Combination Lock
// https://codeforces.com/contest/1097/problem/B

/*
 * Problem: Petr and a Combination Lock
 * Algorithm: Dynamic Programming
 * Techniques: Bitmask / State Transition
 *
 * Time Complexity: O(n * 360) where n <= 15
 * Space Complexity: O(n * 360) which is acceptable given constraints
 *
 * The solution uses dynamic programming to track all possible angles
 * achievable after each rotation. Each rotation can be either clockwise
 * or counterclockwise. We maintain a 2D array p[i][j] where p[i][j] represents
 * the number of ways to reach angle j after i rotations.
 *
 * For each rotation, we update the possible angles by adding or subtracting
 * the rotation angle from the current angles.
 *
 * Finally, if p[n][0] > 0, it means there exists at least one way to make
 * the pointer return to zero after all rotations.
 */

#include <cstdio>

using namespace std;

int i, j, k, n, p[16][360];
int main() {
  p[0][0] = 1; // Base case: 0 rotations -> 1 way to be at angle 0
  for (scanf("%d", &n); i++ < n;)
    for (j = !scanf("%d", &k); j < 360; j++)
      p[i][(j + k) % 360] += p[i - 1][j],       // Add clockwise
          p[i][(j - k + 360) % 360] += p[i - 1][j]; // Add counter-clockwise
  puts(p[n][0] ? "YES" : "NO"); // If there is at least one way to reach 0, output YES
}


// https://github.com/VaHiX/CodeForces/