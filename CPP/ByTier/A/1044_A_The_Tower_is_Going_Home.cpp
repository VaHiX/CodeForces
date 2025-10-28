// Problem: CF 1044 A - The Tower is Going Home
// https://codeforces.com/contest/1044/problem/A

/*
 * Problem: A. The Tower is Going Home
 * Algorithms/Techniques: Sorting, Two Pointers
 * Time Complexity: O(n log n + m log m)
 * Space Complexity: O(n + m)
 *
 * The problem involves finding the minimum number of spells to remove so that
 * a rook can move from (1, 1) to any cell in row 10^9. Spells block movement:
 * - Vertical spells block columns x and x+1
 * - Horizontal spells block segments in rows
 *
 * Approach:
 * 1. Collect all vertical spell positions into array 'a'
 * 2. Collect all horizontal spell start columns into array 'b' (only those with y < 10^9)
 * 3. Sort both arrays
 * 4. For each vertical spell, use two pointers to find how many horizontal spells
 *    block path from left to right at that column.
 * 5. The minimum number of horizontal spells to remove is the minimum value found.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 10;
int n, m, u, v, w, a[maxn], b[maxn], t;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]); // Read vertical spells
  a[n + 1] = 1e9;       // Sentinel value to handle edge case
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (u == 1)         // If it's a vertical spell
      t++, b[t] = v;    // Store its position in b array
  }
  int ans = 1e9;
  sort(a + 1, a + n + 1);    // Sort vertical spell positions
  sort(b + 1, b + t + 1);    // Sort horizontal spell start positions
  int j = 1;                 // Two pointer approach
  for (int i = 1; i <= n + 1; i++) {
    while (j <= t && b[j] < a[i]) // Move j forward while b[j] < a[i]
      j++;
    ans = min(ans, i + t - j);   // Calculate minimum spells needed
  }
  printf("%d\n", ans);
}


// https://github.com/VaHiX/codeForces/