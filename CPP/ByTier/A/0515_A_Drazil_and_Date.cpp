// Problem: CF 515 A - Drazil and Date
// https://codeforces.com/contest/515/problem/A

/*
 * Problem: Drazil and Date
 * Algorithm: Manhattan Distance and Parity Check
 * 
 * Purpose: Determine if it's possible to reach from (0, 0) to (a, b) in exactly s steps,
 *          where each step moves one unit in any of the four cardinal directions.
 * 
 * Key Insight:
 * - The minimum number of steps required is the Manhattan distance: |a| + |b|
 * - If s is less than this distance, it's impossible.
 * - If s is greater than the distance, we can take extra steps by going back and forth.
 * - The difference (s - dist) must be even, because we need to add an even number of steps
 *   to return to the path (e.g., go right then left, or up then down).
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long a, b, s;
  scanf("%ld %ld %ld", &a, &b, &s);
  if (a < 0) {
    a = -a;  // Convert to positive to compute Manhattan distance
  }
  if (b < 0) {
    b = -b;  // Convert to positive to compute Manhattan distance
  }
  long dist = a + b;  // Manhattan distance from (0, 0) to (a, b)
  if (s < dist || (dist - s) % 2 != 0) {
    // If s is less than minimum steps needed OR if (s - dist) is odd,
    // then it is impossible to reach in exactly s steps
    puts("No");
  } else {
    puts("Yes");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/