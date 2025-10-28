// Problem: CF 1824 A - LuoTianyi and the Show
// https://codeforces.com/contest/1824/problem/A

/*
 * Problem: A. LuoTianyi and the Show
 * Algorithm: Greedy + Sorting + Two-Pointer
 * Time Complexity: O(n log n + n + m) per test case
 * Space Complexity: O(n) for storing people's choices
 *
 * The problem requires finding the maximum number of people that can be seated
 * in a row of m seats, depending on the order in which they enter.
 * Each person has one of three ways to sit:
 * 1. Sit to the leftmost available seat (if seat 1 is taken, leave)
 * 2. Sit to the rightmost available seat (if seat m is taken, leave)
 * 3. Sit in a specific seat (if occupied, leave)
 *
 * Strategy:
 * - Remove invalid (-1 or -2) people and count them separately.
 * - Sort valid people who choose specific seats.
 * - Try all possible positions where last person sits to maximize seating.
 * - Use greedy approach with minimum left/right adjustments to compute optimal result.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int x[100010];

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, m, L = 0, R = 0, ans = 0;
    scanf("%d%d", &n, &m);
    // Process input, removing invalid entries (-1 and -2)
    for (int i = 1; i <= n; i++) {
      scanf("%d", &x[i]);
      if (x[i] == -1)
        L++, i--, n--;       // Count leftward requests, move index back
      else if (x[i] == -2)
        R++, i--, n--;       // Count rightward requests, move index back
    }
    sort(x + 1, x + n + 1);      // Sort remaining valid seat choices
    n = unique(x + 1, x + n + 1) - x - 1;   // Remove duplicates
    
    // Two base cases:
    // Case 1: All people fill seats (no gaps, choose min of left/right requests)
    ans = max(n + min(m - n, R), n + min(m - n, L));
    
    // Try placing last person at each available seat to get max result
    for (int i = 1; i <= n; i++)
      ans = max(ans, n + min(x[i] - i, L) + min(m - x[i] - (n - i), R));
    
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/