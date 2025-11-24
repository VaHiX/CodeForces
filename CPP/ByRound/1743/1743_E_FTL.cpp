// Problem: CF 1743 E - FTL
// https://codeforces.com/contest/1743/problem/E

/*
 * Purpose: This code solves the problem of finding the minimum time to destroy an enemy spaceship
 *          using two lasers with different powers and reload times. It uses dynamic programming
 *          with an optimized approach that considers all possible combinations of shooting
 *          single or both lasers.
 *
 * Algorithms/Techniques: Dynamic Programming with optimized iteration over combinations of
 *                        laser firing patterns.
 *
 * Time Complexity: O(h * h) where h is the durability of the enemy spaceship.
 * Space Complexity: O(h) for the dp array.
 */

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  long long p1, t1, p2, t2, h, s;
  cin >> p1 >> t1 >> p2 >> t2 >> h >> s;
  long long dp[h + 1]; // dp[i] represents the minimum time to deal i damage
  memset(dp, 0x3f, sizeof(dp)); // Initialize all values to a large number (infinity)
  dp[0] = 0; // Base case: 0 damage requires 0 time

  // For each amount of damage (from 1 to h)
  for (int i = 1; i <= h; i++) {
    // Try all possible numbers of consecutive shots (j)
    for (int j = 1; j <= i; j++) {
      // Case 1: Fire laser 1 first, then laser 2 in sync
      long long dlt = j * (p1 - s) + (j * t1 / t2) * (p2 - s) + (j * t1 >= t2 ? s : 0);
      if (dlt >= i) {
        // If the total damage is enough, just use j * t1 time
        dp[i] = min(dp[i], j * t1);
      } else {
        // Otherwise, we need to account for additional time to reach the damage
        dp[i] = min(dp[i], dp[i - dlt] + j * t1);
      }

      // Case 2: Fire laser 2 first, then laser 1 in sync
      dlt = j * (p2 - s) + (j * t2 / t1) * (p1 - s) + (j * t2 >= t1 ? s : 0);
      if (dlt >= i) {
        // If the total damage is enough, just use j * t2 time
        dp[i] = min(dp[i], j * t2);
      } else {
        // Otherwise, we need to account for additional time to reach the damage
        dp[i] = min(dp[i], dp[i - dlt] + j * t2);
      }
    }
  }

  cout << dp[h] << endl; // Output minimum time for h damage
  return 0;
}


// https://github.com/VaHiX/CodeForces/