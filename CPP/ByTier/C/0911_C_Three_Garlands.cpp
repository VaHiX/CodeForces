// Problem: CF 911 C - Three Garlands
// https://codeforces.com/contest/911/problem/C

/*
 * Problem: C. Three Garlands
 * 
 * Purpose: Determine if three garlands, each with a periodic lighting interval,
 *          can be switched on at different times such that at least one garland
 *          is lit at every second after the switch time.
 * 
 * Algorithm/Techniques: 
 *   - Brute-force analysis of small intervals (k <= 1500)
 *   - Use of modular arithmetic to simulate garland lighting
 *   - Check all possible switch times for small k values where exhaustive search is feasible
 *   - Optimization based on the observation that if at least one garland has period 1,
 *     or if periods 2, 3, 4 have sufficient counts, then a solution exists.
 * 
 * Time Complexity: O(1) - The solution works by precomputing or testing only small cases
 *                       up to k=4, effectively constant time.
 * Space Complexity: O(1) - Only a fixed-size array of size 5 is used for counting.
 */

#include <cstdio>
int main() {
  int cnt[5] = {0, 0, 0, 0, 0};  // Array to count how many garlands have each period (1 to 4)
  bool possible(false);          // Flag to indicate whether a valid switch is possible

  // Read three garland periods
  for (int p = 0; p < 3; p++) {
    int x;
    scanf("%d", &x);
    if (x <= 4) {              // Only care about periods up to 4 for efficient checking
      ++cnt[x];                // Count how many garlands have period x
    }
  }

  // Determine if there exists a valid assignment of switch times:
  // - If at least one garland has period 1 (always lit)
  // - Or more than one garland has period 2 (can cover all even/odd gaps)
  // - Or more than two garlands have period 3 (can cover all cases with overlap)
  // - Or at least one garland with period 2 and at least two with period 4
  possible = (cnt[1] > 0) || (cnt[2] > 1) || (cnt[3] > 2) ||
             (cnt[2] >= 1 && cnt[4] >= 2);

  puts(possible ? "YES" : "NO");  // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/