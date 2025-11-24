// Problem: CF 1772 F - Copy of a Copy of a Copy
// https://codeforces.com/contest/1772/problem/F

/*
Code Purpose:
This program reconstructs the sequence of operations performed on a binary matrix (picture), 
based on multiple copies of the picture and the initial state. The operations are:
1. Recolor a cell if it's surrounded by four opposite-colored neighbors (not on border)
2. Make a copy of the current picture

The solution works by:
- Calculating for each picture how many cells satisfy the "surrounded by four opposite colors" condition
- Sorting pictures by this count (descending)
- Identifying operations by comparing adjacent pictures in this sorted order:
  - If a cell is not surrounded in the previous picture but is in the current, and has different color, it means it was flipped
  - Each flip is followed by a copy operation

Algorithms/Techniques:
- Preprocessing: Count valid cells (surrounded by 4 opposite colors) for each picture
- Sorting: Sort pictures by count of valid cells (descending)
- Simulation: Compare adjacent pictures to detect flips and copy operations
- Greedy matching: Assume the picture with the highest count is the last one (final state)

Time Complexity:
O(k * n * m) for preprocessing of all pictures, O(k log k) for sorting, O(k * n * m) for determining operations
Overall: O(k * n * m)

Space Complexity:
O(k * n * m) for storing pictures + O(k) for auxiliary structures
Overall: O(k * n * m)
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int INF = 1e9;
struct S {
  int id, sum;
} a[110];
int n, m, k, q, dir[110], op[1000010], X[1000010], Y[1000010], ss;
char s[110][40][40];
bool cmp(S x, S y) { return x.sum > y.sum; }
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k + 1; i++) {
    a[i].id = i;
    for (int j = 1; j <= n; j++)
      scanf("%s", s[i][j] + 1);
    for (int j = 2; j < n; j++)
      for (int k = 2; k < m; k++) {
        // Check if cell (j,k) is surrounded by 4 cells of opposite color
        if (s[i][j][k] != s[i][j - 1][k] && s[i][j][k] != s[i][j + 1][k] &&
            s[i][j][k] != s[i][j][k + 1] && s[i][j][k] != s[i][j][k - 1])
          a[i].sum++;
      }
  }
  sort(a + 1, a + k + 2, cmp); // Sort by number of valid cells (descending)
  printf("%d\n", a[1].id); // The initial picture is the one with minimum valid cells 
  for (int i = 2, p, q; i <= k + 1; i++) {
    p = a[i].id, q = a[i - 1].id; // p is current picture, q is previous picture
    for (int j = 2; j < n; j++)
      for (int k = 2, x, y; k < m; k++) {
        x = y = 0;
        // Check if cell (j,k) in picture p is surrounded
        if (s[p][j][k] != s[p][j - 1][k] && s[p][j][k] != s[p][j + 1][k] &&
            s[p][j][k] != s[p][j][k + 1] && s[p][j][k] != s[p][j][k - 1])
          x = 1;
        // Check if cell (j,k) in picture q is surrounded
        if (s[q][j][k] != s[q][j - 1][k] && s[q][j][k] != s[q][j + 1][k] &&
            s[q][j][k] != s[q][j][k + 1] && s[q][j][k] != s[q][j][k - 1])
          y = 1;
        // If q had surrounded cell but p doesn't, and they're different, it means it was flipped
        if (x == 0 && y == 1 && s[p][j][k] != s[q][j][k])
          op[++ss] = 1, X[ss] = j, Y[ss] = k; // Record flip operation
      }
    op[++ss] = 2, X[ss] = p; // Record copy operation (copy picture p)
  }
  printf("%d\n", ss); // Print number of operations
  for (int i = 1; i <= ss; i++) {
    if (op[i] == 1)
      printf("1 %d %d\n", X[i], Y[i]); // Print flip operation
    else
      printf("2 %d\n", X[i]); // Print copy operation
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/