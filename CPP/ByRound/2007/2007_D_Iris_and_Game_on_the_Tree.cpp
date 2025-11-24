// Problem: CF 2007 D - Iris and Game on the Tree
// https://codeforces.com/contest/2007/problem/D

// Problem: D. Iris and Game on the Tree
// Purpose: Determine the final score of a tree game where players alternate filling '?'
//          values to maximize/minimize the number of leaves with non-zero weight.
// Algorithms/Techniques: Tree traversal, game theory (minimax), greedy strategy.
// Time Complexity: O(n) per test case
// Space Complexity: O(n)

#include <algorithm>
#include <stdio.h>
const int N = 200005;
int T, n, m;
int c[2], d[N];  // c[0] and c[1] count of leaves with fixed values 0 and 1 respectively
char s[N];
signed main() {
  int i, u, v;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
      d[i] = 0;
    for (i = 1; i < n; i++) {  // Read edges and count degrees
      scanf("%d%d", &u, &v);
      d[u]++, d[v]++;
    }
    scanf("%s", s + 1);
    c[0] = c[1] = m = v = 0;
    for (i = 2; i <= n; i++)  // Process leaves and '?'
      if (d[i] == 1) {  // If leaf
        if (s[i] == '?')
          m++;  // Count '?' at leaf positions
        else
          c[s[i] ^ 48]++;  // Convert char to int and count 0/1
      } else if (s[i] == '?')  // Non-leaf '?'
        v ^= 1;  // Toggle flag to track parity of '?'

    // Game logic based on root value
    if (s[1] == '?') {
      // Root is unfixed: Iris chooses to maximize score, Dora minimizes
      if (c[0] ^ c[1])
        // If counts differ, Iris can choose one value and Dora will match it optimally
        printf("%d\n", m / 2 + std::max(c[0], c[1]));
      else
        // If counts are equal, tie-breaker with half of '?' to minimize impact
        printf("%d\n", m / 2 + c[0] + (m & v));
    } else
      // Root is fixed: Iris has direct advantage for that value
      printf("%d\n", (m + 1) / 2 + c[s[1] ^ 49]);  // s[1]^49 gives the other bit
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/