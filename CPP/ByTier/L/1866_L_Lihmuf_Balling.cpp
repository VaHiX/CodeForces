// Problem: CF 1866 L - Lihmuf Balling
// https://codeforces.com/contest/1866/problem/L

/*
 * Problem: Choose optimal K for Lihmuf to maximize balls collected.
 * Algorithm: Brute force over all possible K values from 1 to M.
 * For each K, simulate the game and compute total balls Lihmuf gets.
 * Key idea: On turn j, Pak Chanek picks box j, Lihmuf picks box y = ((j*K - 1) % N) + 1.
 * Boxes can only be picked once per simulation.
 *
 * Time Complexity: O(M * N), where M <= 2000 and N <= 1e9,
 *                   but due to early termination and optimization, effectively much less.
 * Space Complexity: O(N), for the boolean array b[] of size N.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2010;
int b[N]; // Boolean array to track which boxes have been picked
int n, m; // Number of boxes and max K value

int main() {
  scanf("%d%d", &n, &m);
  long long an = 0; // Maximum balls Lihmuf can collect
  int p = 1;        // Optimal K value to return

  // Try all possible values of K from 1 to M
  for (int i = 2; i <= m; i++) {
    // Reset the box picking tracker for current K
    for (int j = 1; j <= i; j++)
      b[j] = 0;

    int x = i;        // Current box Lihmuf will pick
    int y = 1;        // Next turn index (1-based)
    long long s = 0;  // Total balls collected by Lihmuf in this simulation

    // Simulate the game until all boxes are exhausted or cycle detected
    while (!b[x] && x <= n) {
      b[x] = 1; // Mark box x as picked

      // Compute how many times we can iterate before going out of bounds
      int t = (n - x) / i;
      int t1;

      // Adjust t1 based on y and x
      if (y - x < 0)
        t1 = 0;
      else
        t1 = (y - x) / (i - 1) + 1;

      // If valid range exists, accumulate balls accordingly
      if (t1 <= t) {
        s += 1ll * x * (t - t1 + 1) + 1ll * (t1 + t) * (t - t1 + 1) / 2 * i;
      }

      // Update box index for next iteration
      x = x + (t + 1) * i - n;
      y += (t + 1); // Increment turn counter
    }

    // If this K gives better result, update max and best K
    if (an < s) {
      an = s;
      p = i;
    }
  }

  printf("%d\n", p);
}


// https://github.com/VaHiX/codeForces/