// Problem: CF 2022 C - Gerrymandering
// https://codeforces.com/contest/2022/problem/C

/*
C. Gerrymandering
Algorithm: Dynamic Programming with state tracking of optimal district selection
Time Complexity: O(n) per test case
Space Complexity: O(n) for the DP array f

This problem involves dividing a 2xN grid into districts of 3 connected cells each,
where each district votes for Álvaro if at least 2 of its 3 cells vote for him.
The goal is to maximize the number of districts that vote for Álvaro by choosing
optimal grouping of cells.

Approach:
- Use dynamic programming where f[i] represents the maximum number of districts
  that can be won up to column i.
- For each position i, we consider various patterns of how 3 consecutive cells
  can form a district (based on their connections and votes).
- The recurrence considers transitions based on modulo 3 conditions to optimize
  district construction.

*/

#include <algorithm>
#include <iostream>

using namespace std;
int t, n, f[100005], i, j;
char c[2][100005];

// Check if a district formed by 3 cells votes for Álvaro (at least 2 A's)
int ck(int xa, int ya, int xb, int yb, int xc, int yc) {
  int res = 0;
  if (c[ya][xa] == 'A')
    res++;
  if (c[yb][xb] == 'A')
    res++;
  if (c[yc][xc] == 'A')
    res++;
  if (res >= 2)
    return 1;
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 0; i <= 1; i++)
      for (j = 1; j <= n; j++)
        cin >> c[i][j];
    for (i = 1; i <= n; i++)
      f[i] = 0;
    for (i = 1; i <= n; i++) {
      // Calculate j based on pattern matching for district construction
      j = i + (i + 1) % 3 - 1;
      if (i >= 3)
        f[i] = f[i - 3] + ck(i - 2, 0, i - 1, 0, i, 0) +
               ck(j - 2, 1, j - 1, 1, j, 1);
      // Handle transitions for modulo cases to optimize district choices
      if (i % 3 == 0)
        f[i] = max(f[i], max(f[i - 2] + ck(i - 1, 0, i, 0, i, 1),
                             f[i - 1] + ck(i, 0, i - 1, 1, i, 1)));
      else if (i % 3 == 1)
        f[i] = max(f[i], f[i - 1] + ck(i, 0, i, 1, i + 1, 1));
      else
        f[i] = max(f[i], f[i - 2] + ck(i - 1, 0, i, 0, i - 1, 1));
    }
    cout << f[n] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/