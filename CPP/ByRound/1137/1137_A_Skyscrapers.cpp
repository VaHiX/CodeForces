// Problem: CF 1137 A - Skyscrapers
// https://codeforces.com/contest/1137/problem/A

/*
 * Problem: Dora's Skyscraper Height Assignment
 * Task: For each intersection (i,j), determine the minimum possible maximum height x
 *       when reassigning heights to skyscrapers on row i and column j such that:
 *       - Relative order of skyscrapers in row i is preserved
 *       - Relative order of skyscrapers in column j is preserved
 *
 * Approach:
 * 1. For each row i, calculate ranking (num[i][j]) based on relative heights of elements in that row.
 * 2. For each column j, calculate ranking (num2[i][j]) based on relative heights of elements in that column.
 * 3. For each intersection (i,j), compute:
 *    - mx1[i]: maximum rank in row i
 *    - mx2[j]: maximum rank in column j
 *    - mn = max(num[i][j], num2[i][j]): minimum required rank at current position
 *    - result = max(mn + mx1[i] - num[i][j], mn + mx2[j] - num2[i][j])
 *
 * Time Complexity: O(n * m * log(m) + n * m)
 * Space Complexity: O(n * m)
 */
#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
pair<int, int> tmp[1010]; // Temporary array to sort elements
int n, m, a[1010][1010], num[1010][1010], mx1[1010], mx2[1010],
    num2[1010][1010];
int main() {
  scanf("%d%d", &n, &m); // Read dimensions n and m
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &a[i][j]); // Read matrix a

  // Process each row: assign ranks to elements in the row
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      tmp[j] = make_pair(a[i][j], j); // Store height and column index
    sort(tmp + 1, tmp + 1 + m);       // Sort by height
    
    int tot = 0; // Rank counter
    for (int j = 1; j <= m; j++) {
      if (tmp[j].first != tmp[j - 1].first) // If new unique value
        tot++; // Increment rank
      num[i][tmp[j].second] = tot; // Assign rank to corresponding column index
    }
    mx1[i] = tot; // Store maximum rank for this row
  }

  // Process each column: assign ranks to elements in the column
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++)
      tmp[j] = make_pair(a[j][i], j); // Store height and row index
    sort(tmp + 1, tmp + 1 + n);       // Sort by height
    
    int tot = 0; // Rank counter
    for (int j = 1; j <= n; j++) {
      if (tmp[j].first != tmp[j - 1].first) // If new unique value
        tot++; // Increment rank
      num2[tmp[j].second][i] = tot; // Assign rank to corresponding row index
    }
    mx2[i] = tot; // Store maximum rank for this column
  }

  // Compute answers for each intersection (i,j)
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int mn = max(num[i][j], num2[i][j]); // Minimum required rank at (i,j)
      // Compute the final answer using two possible scenarios:
      // 1. Use row-based assignment
      // 2. Use column-based assignment
      printf("%d ", max(mn + mx1[i] - num[i][j], mn + mx2[j] - num2[i][j]));
    }
    puts(""); // Newline after each row
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/