// Problem: CF 697 A - Pineapple Incident
// https://codeforces.com/contest/697/problem/A

/*
 * Problem: Pineapple Incident
 * Purpose: Determine if a pineapple barks at a given time 'x', based on its barking pattern.
 * 
 * Barking pattern:
 * - First bark at time `t`
 * - Then every `s` seconds, it barks twice with 1 second interval
 * - So barks at: t, t+s, t+s+1, t+2s, t+2s+1, ...
 * 
 * Algorithm:
 * 1. Check if x equals t (first bark)
 * 2. Otherwise, check if (x - t) is a valid time for the pattern:
 *    - The difference (x - t) must be divisible by s or (x - t) % s <= 1
 *    - This accounts for the two barks per s-second interval
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of variables
 */

#include <cstdio>
int main() {
  long t, s, x;
  scanf("%ld %ld %ld\n", &t, &s, &x);
  puts(((x == t) || (((x - t) / s > 0) && ((x - t) % s <= 1))) ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/