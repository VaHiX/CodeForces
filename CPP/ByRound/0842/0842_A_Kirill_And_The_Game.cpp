// Problem: CF 842 A - Kirill And The Game
// https://codeforces.com/contest/842/problem/A

/*
 * Problem: Kirill And The Game
 * Purpose: Determine if there exists a potion with efficiency exactly k,
 *          where efficiency = experience / cost.
 *          Potions have experience in range [l, r] and cost in range [x, y].
 *          
 * Algorithm: 
 *   - For each possible cost p in [x, y], check if there exists an experience
 *     value in [l, r] such that experience/cost = k.
 *     This is equivalent to checking if l <= k*p <= r.
 *   - Since k*p must be in [l, r], we can iterate over all possible costs p
 *     and see if such an experience exists.
 *   
 * Time Complexity: O(y - x + 1) in worst case, but can be optimized to O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long long l, r, x, y, k;
  scanf("%lld %lld %lld %lld %lld", &l, &r, &x, &y, &k);
  bool possible = false;
  // Iterate through all possible costs from x to y
  for (long p = x; p <= y; p++) {
    // Check if k * p is within the experience range [l, r]
    if (l <= k * p && k * p <= r) {
      possible = true;
      break;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/