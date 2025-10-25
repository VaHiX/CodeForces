// Problem: CF 2073 A - Control Towers
// https://codeforces.com/contest/2073/problem/A

/*
Control Towers
Input file: standard input
Output file: standard output
Time limit: 2 seconds
Memory limit: 1024 megabytes

Problem Description:
You are given a 2D grid with empty cells ('.') and occupied cells ('#'). 
Place four control towers in different empty cells such that for all consecutive towers k and k+1,
they are either in the same row or same column. This is essentially counting valid sequences of
4 points where each point shares a row or column with the next.

Approach:
- Precompute row and column counts of empty cells.
- Count contributions from rows and columns independently using combinatorics:
  For a row/column with 'r' empty cells, number of ways to choose 4 sequential cells = C(r,4).
- Then handle transitions (tower k and k+1 in same row/column):
  For each cell (i,j) with '.', we consider it as part of a path. 
  We track how many previous choices have led us to current column/row.

Time Complexity: O(n * m)
Space Complexity: O(n + m)

Algorithms/Techniques:
- Combinatorics for counting
- Preprocessing of row/column counts
- Two-pass approach with tracking variables

*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
char s[2004][2004];
int n, m, r[2004], c[2004], w[2004]; // r: row counts, c: col counts, w: column weight for transitions
ll ans;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%s", s[i]); // Read the grid

  // Count empty cells per row and column
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (s[i][j] == '.')
        r[i]++, c[j]++; // Increment row and column counters

  // Add combinations for rows: C(r[i], 4) = r[i] * (r[i]-1) * (r[i]-2) * (r[i]-3) / 24
  for (int i = 0; i < n; i++)
    ans += (ll)r[i] * (r[i] - 1) * (r[i] - 2) * (r[i] - 3);

  // Add combinations for columns: same as rows
  for (int i = 0; i < m; i++)
    ans += (ll)c[i] * (c[i] - 1) * (c[i] - 2) * (c[i] - 3);

  // Loop through each row to calculate cross-row/column transitions
  for (int i = 0; i < n; i++) {
    int t = 0; // tracks cumulative column contributions from previous rows in this row
    for (int j = 0; j < m; j++)
      if (s[i][j] == '.') { // Only process empty cells
        // Add transition terms: two paths involving current cell and prior choices
        ans += 2ll * (r[i] - 1) * (c[j] - 1) * (r[i] + c[j] - 4); // Transition from row to col or vice versa
        ans += 2ll * w[j] * (r[i] - 1), w[j] += r[i] - 1, // Update column weight
            ans += 2ll * t * (c[j] - 1), t += c[j] - 1; // Update row weight and accumulate transitions
      }
  }
  printf("%lld", ans); // Output result
}


// https://github.com/VaHiX/codeForces/