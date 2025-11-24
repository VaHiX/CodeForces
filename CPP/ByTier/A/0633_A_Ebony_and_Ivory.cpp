// Problem: CF 633 A - Ebony and Ivory
// https://codeforces.com/contest/633/problem/A

/*
 * Problem: Ebony and Ivory
 * Purpose: Determine if it's possible to deal exactly 'c' units of damage
 *          using two guns that deal 'a' and 'b' damage per shot respectively.
 * Algorithm: Dynamic Programming approach using a boolean vector to track
 *            achievable damage values up to 'c'.
 * 
 * Time Complexity: O(c), where c is the target damage.
 * Space Complexity: O(c), for the boolean vector of size c+1.
 * 
 * Techniques: 
 * - Dynamic Programming
 * - Bitmask-style simulation of reachable sums
 */

#include <cstdio>
#include <vector>
int main() {
  int a, b, c;
  scanf("%d %d %d\n", &a, &b, &c);
  std::vector<bool> possible(c + 1, 0);  // possible[i] indicates if damage i is achievable
  possible[0] = 1;  // Base case: 0 damage is always achievable (0 shots)
  for (int p = 0; p <= c; p++) {
    if (!possible[p]) {
      continue;  // Skip if current damage value is not achievable
    }
    if (p + a <= c) {
      possible[p + a] = 1;  // Mark damage +a as achievable
    }
    if (p + b <= c) {
      possible[p + b] = 1;  // Mark damage +b as achievable
    }
  }
  puts(possible[c] ? "Yes" : "No");  // Output result based on whether target damage is achievable
  return 0;
}


// https://github.com/VaHiX/CodeForces/