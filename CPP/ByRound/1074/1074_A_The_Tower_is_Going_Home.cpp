// Problem: CF 1074 A - The Tower is Going Home
// https://codeforces.com/contest/1074/problem/A

/*
 * Problem: A. The Tower is Going Home
 * Algorithm/Techniques: Two Pointers + Sorting
 *
 * Time Complexity: O(n log n + m log m)
 * Space Complexity: O(n + m)
 *
 * Description:
 * This code finds the minimum number of spells to remove so that a rook can travel 
 * from (1, 1) to any cell in row 10^9. It handles two types of spells:
 * - Vertical: block column x and x+1
 * - Horizontal: block segment in row y from x1 to x2
 *
 * The solution sorts vertical and horizontal spell positions and uses a two-pointer 
 * technique to determine the minimum number of spells that must be removed.
 */

#include <stdio.h>
#include <algorithm>

#define inf 0x3f3f3f3f
using namespace std;

int a[100005], b[100005]; // a stores vertical spell positions, b stores horizontal spell start points

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  a[++n] = 1e9; // Append a large value to handle edge cases
  int cnt = 0;
  for (int i = 1; i <= m; i++) {
    int x1, x2, y;
    scanf("%d%d%d", &x1, &x2, &y);
    if (x1 == 1) // Only consider horizontal spells that start at column 1
      b[++cnt] = x2;
  }
  sort(a + 1, a + n + 1); // Sort vertical spells
  sort(b + 1, b + cnt + 1); // Sort horizontal spell endpoints
  int r = 1, ans = inf;
  for (int i = 1; i <= n; i++) {
    while (r <= cnt && b[r] < a[i]) // Move pointer r to find first b[r] >= a[i]
      r++;
    ans = min(ans, cnt - r + i); // Calculate minimal removals needed
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/