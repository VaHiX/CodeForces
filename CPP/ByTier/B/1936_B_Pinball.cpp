// Problem: CF 1936 B - Pinball
// https://codeforces.com/contest/1936/problem/B

/*
 * Problem: Pinball on a 1D Grid
 *
 * Purpose: For each position on a 1D grid, simulate a pinball that moves according to
 *          the direction of the character in that cell. The character changes after
 *          the pinball passes through it. Calculate the time until the pinball leaves
 *          the grid.
 *
 * Algorithm:
 * - Preprocess the grid to track cumulative sums and counts of '<' and '>' characters.
 * - Use prefix sums and cumulative counts to efficiently compute the total time for each
 *   starting position.
 * - For each starting position, calculate how long the pinball stays inside the grid,
 *   taking into account the changing directions.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing prefix arrays and counters
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
char s[500005];
int cntl[500005], cntr[500005];
ll suml[500005], sumr[500005];

// Return -1 for '>' and 1 for '<'
int sign(char c) {
  if (c == '>')
    return -1;
  return 1;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    scanf("%s", s + 1);
    int pl = 0, pr = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i] == '<') {
        // Count of '<' so far
        cntl[i] = cntl[i - 1] + 1, cntr[i] = cntr[i - 1];
        // Add position to suml
        suml[pl + 1] = suml[pl] + i;
        ++pl;
      } else {
        // Count of '>' so far
        cntl[i] = cntl[i - 1], cntr[i] = cntr[i - 1] + 1;
        // Add position to sumr
        sumr[pr + 1] = sumr[pr] + i;
        ++pr;
      }
    }
    // Process positions where s[i] == '<'
    for (int i = 1; i <= pl; i++)
      printf("%lld ", (suml[i] - suml[cntl[i]] - sumr[cntr[i - 1]]) * 2 +
                          sign(s[i]) * i);
    // Process positions where s[i] == '>'
    for (int i = pl + 1; i <= n; i++)
      printf("%lld ", n + 1 +
                          (suml[pl] - suml[cntl[i]] - sumr[cntr[i - 1]] +
                           sumr[i - 1 - pl]) *
                              2 +
                          sign(s[i]) * i);
    printf("\n");
  }
}


// https://github.com/VaHiX/CodeForces/