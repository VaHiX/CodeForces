// Problem: CF 1580 A - Portal
// https://codeforces.com/contest/1580/problem/A

/*
Algorithm: Portal
Purpose: Find the minimum number of operations to transform a given n x m grid into one that contains at least one valid portal sub-rectangle.
A portal is defined as an a x b rectangle where:
  - a >= 5, b >= 4
  - All edges except corners must be obsidian (1), and all inner cells must be empty (0)
  - Corners can be any type

Time Complexity: O(n^2 * m^2) where n,m <= 400
Space Complexity: O(n * m)

Approach:
- Precompute prefix sums for rows to efficiently check number of 1s in a range.
- Enumerate all possible top-left positions (i,j) of potential portals.
- For each such position, enumerate potential right edge k > j+2.
- Calculate cost to make boundary edges obsidian and inner part empty.
- Use precomputed prefix sums to count 0s in rows for efficiency.
*/
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 409;
char s[N][N];
int p[N][N]; // Prefix sum of 1s in each row
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T, n, m, i, j, k, l, ans, now, tot;
  cin >> T;
  while (T--) {
    cin >> n >> m, ans = 20; // Initialize answer with high value
    for (i = 1; i <= n; ++i)
      cin >> (s[i] + 1);   // Read input grid starting from index 1
    // Precompute prefix sums for each row
    for (i = 1; i <= n; ++i)
      for (j = 1; j <= m; ++j)
        p[i][j] = p[i][j - 1] + (s[i][j] == '1');

    // Enumerate top-left corner (i,j) of a potential portal
    for (i = 1; i <= n; ++i)
      for (j = 1; j <= m; ++j) {
        tot = 0;
        // Extend right edge to k, k > j+2
        for (k = j + 1; k < m; ++k) {
          tot += (s[i][k] == '0');   // Count how many 0s we need to change
          if (tot >= ans)            // Early termination if cost exceeds current best
            break;
          if (k >= j + 2) {           // At least width 4
            now = tot;               // Initialize with changes to right edge
            // Enumerate bottom edge from l = i+1
            for (l = i + 1; l < n; ++l) {
              // Add new row's contribution to the cost of making edges obsidian
              now +=
                  p[l][k] - p[l][j] + (s[l][j] == '0') + (s[l][k + 1] == '0');
              if (now >= ans)
                break;
              // When we have at least 5 rows, check for valid portal
              if (l >= i + 3)
                ans = min(ans, now + k - j - p[l + 1][k] + p[l + 1][j]);
            }
          }
        }
      }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/