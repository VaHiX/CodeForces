// Problem: CF 1863 D - Two-Colored Dominoes
// https://codeforces.com/contest/1863/problem/D

/*
 * Problem: D. Two-Colored Dominoes
 * 
 * Algorithm/Technique:
 * - This solution uses a greedy approach to color the dominoes.
 * - For each column, we process 'L' domino halves and assign colors to ensure
 *   that each domino has one black and one white cell.
 * - Similarly, for each row, we process 'U' domino halves.
 * - The parity of dominoes in each row/column must be even for a valid coloring.
 * 
 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m)
 * 
 * The algorithm processes each cell once, and the nested loops iterate through
 * rows and columns, making it linear in terms of the total number of cells.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 510;
char s[N][N];
int T, n, m;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
      scanf("%s", s[i] + 1);
    int flag = 1;
    // Process columns: handle 'L' domino halves
    for (int j = 1; j <= m; j++) {
      int op = 0;
      for (int i = 1; i <= n; i++)
        if (s[i][j] == 'L') {
          // Assign alternating colors to the domino (L -> R)
          if (op)
            s[i][j] = 'W', s[i][j + 1] = 'B';  // If previous domino was colored, assign opposite colors
          else
            s[i][j] = 'B', s[i][j + 1] = 'W';  // else assign normal colors
          op ^= 1;  // Toggle the parity flag for next domino in same column
        }
      if (op)  // If column ends with an unpaired domino, painting is impossible
        flag = 0;
    }
    // Process rows: handle 'U' domino halves
    for (int i = 1; i <= n; i++) {
      int op = 0;
      for (int j = 1; j <= m; j++)
        if (s[i][j] == 'U') {
          // Assign alternating colors to the domino (U -> D)
          if (op)
            s[i][j] = 'W', s[i + 1][j] = 'B';  // If previous domino was colored, assign opposite colors
          else
            s[i][j] = 'B', s[i + 1][j] = 'W';  // else assign normal colors
          op ^= 1;  // Toggle the parity flag for next domino in same row
        }
      if (op)  // If row ends with an unpaired domino, painting is impossible
        flag = 0;
    }
    if (flag) {
      // Print result
      for (int i = 1; i <= n; i++)
        printf("%s\n", s[i] + 1);
    } else
      puts("-1");
  }
}


// https://github.com/VaHiX/CodeForces/