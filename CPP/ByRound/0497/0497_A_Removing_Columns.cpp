// Problem: CF 497 A - Removing Columns
// https://codeforces.com/contest/497/problem/A

/*
Purpose: 
This code determines the minimum number of columns to remove from an n×m table of lowercase letters 
such that the remaining rows are ordered lexicographically from top to bottom. 
It uses a greedy approach to check for valid column sequences and marks rows as "good" when 
they have been successfully compared in order.

Algorithms/Techniques:
- Greedy approach: Process columns one by one from left to right
- Row flag marking: Use array `a` to track which rows are already in correct order
- Lexicographical comparison: Compare adjacent rows in each column to decide if the column should be removed

Time Complexity: O(n * m)
Space Complexity: O(n * m) for storing the table and O(n) for the flag array `a`

*/
#include <cstdio>
#include <iosfwd>

using namespace std;
int n, m, i, ans, j, a[110], flag;
char s1[110][110];
int main() {
  scanf("%d%d", &n, &m);
  for (i = 1; i <= n; i++)
    scanf("%s", s1[i] + 1); // Read each row into the 1-based table
  for (i = 1; i <= m; i++) { // Process each column
    for (j = 2; j <= n; j++)
      if (s1[j][i] < s1[j - 1][i] && !a[j]) // If current row's char is smaller than previous and not marked as good
        flag = 1; // Mark this column for removal
    if (flag)
      ans++; // Increment removal count
    else
      for (j = 2; j <= n; j++)
        if (s1[j][i] > s1[j - 1][i]) // If current row's char is larger than previous
          a[j] = 1; // Mark this row as good (now in correct order)
    flag = 0; // Reset flag for next column
  }
  printf("%d\n", ans); // Output minimum number of columns to remove
}


// https://github.com/VaHiX/CodeForces/