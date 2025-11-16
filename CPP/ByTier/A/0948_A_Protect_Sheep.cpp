// Problem: CF 948 A - Protect Sheep
// https://codeforces.com/contest/948/problem/A

/*
 * Problem: Protect Sheep
 * 
 * Algorithm/Technique: 
 * - Greedy approach on grid
 * - For each empty cell ('.'), place a dog ('D')
 * - For each sheep ('S'), check if any adjacent cell has a wolf ('W')
 *   - If so, output "No" (impossible)
 * - If no conflicts, output "Yes" and the resulting grid
 * 
 * Time Complexity: O(R * C)
 * - We iterate through each cell once to check for wolves adjacent to sheep
 * - Then another pass to place dogs in empty cells
 * 
 * Space Complexity: O(R * C)
 * - Storing the grid of size R x C
 */

#include <stdio.h>
char s[505][505];
int n, k, i, j;
int main() {
  scanf("%d%d", &n, &k);
  for (i = 1; i <= n; i++)
    scanf("%s", s[i] + 1);
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= k; j++) {
      // If cell is empty, place a dog
      if (s[i][j] == '.')
        s[i][j] = 'D';
      // If cell is a sheep and any of its neighbor is a wolf, it's impossible to protect
      if (s[i][j] == 'S' && (s[i + 1][j] == 'W' || s[i - 1][j] == 'W' ||
                             s[i][j + 1] == 'W' || s[i][j - 1] == 'W')) {
        puts("No");
        return 0;
      }
    }
  }
  puts("Yes");
  for (i = 1; i <= n;)
    printf("%s\n", s[i++] + 1);
}


// https://github.com/VaHiX/CodeForces/