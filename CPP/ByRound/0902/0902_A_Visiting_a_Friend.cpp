// Problem: CF 902 A - Visiting a Friend
// https://codeforces.com/contest/902/problem/A

/*
 * Problem: Visiting a Friend
 * 
 * Purpose: Determine if Pig can reach his friend's house at point `m` using only teleports.
 *          Each teleport is defined by its location `a` and limit `b`, allowing movement from `a` to any point in `[a, b]`.
 * 
 * Algorithm: Greedy approach
 *   - Start at position 0 (Pig's house)
 *   - For each teleport, if it's reachable from current position (`a <= x`), update the furthest reachable position (`x = max(x, b)`)
 *   - If at any point the current reachable position reaches or exceeds `m`, return "YES"
 *   - If all teleports are processed and `m` is not reached, return "NO"
 * 
 * Time Complexity: O(n) - single pass through the teleports
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  long x(0); // current reachable position, starts at 0 (Pig's house)
  bool possible(false); // flag to indicate whether target is reachable
  for (long p = 0; p < n; p++) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (a <= x) { // if current teleport is reachable from x
      x = (x > b) ? x : b; // update x to the furthest point reachable by this or previous teleports
    }
    if (m <= x) { // if we can now reach or surpass the friend's house
      possible = true;
      break;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/