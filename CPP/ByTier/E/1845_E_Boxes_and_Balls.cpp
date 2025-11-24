// Problem: CF 1845 E - Boxes and Balls
// https://codeforces.com/contest/1845/problem/E

/*
 * Problem: Boxes and Balls
 * 
 * Purpose:
 *   Given n boxes arranged in a line, some containing balls (1) and others empty (0),
 *   perform exactly k moves. Each move involves moving a ball from a box with a ball 
 *   to an adjacent empty box. Count the number of distinct final arrangements possible 
 *   after exactly k moves.
 * 
 * Algorithm:
 *   Dynamic Programming with Optimization:
 *   - State: f[j][k] = number of ways to place j balls at positions such that 
 *     total moves used is exactly k.
 *   - For each box i (from 1 to n), compute how many balls can be moved to it 
 *     based on current positions of balls.
 *   - Use a rolling technique by restricting the range of j to avoid recomputation.
 *   - Use prefix sums or memoization to optimize transitions.
 * 
 * Time Complexity: O(n * sqrt(k) * k) = O(n * k^(3/2))
 * Space Complexity: O(n * k)
 * 
 * Techniques:
 *   - Dynamic Programming
 *   - Range Optimization using sqrt decomposition
 *   - Efficient transitions using precomputed positions
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define ri register
#define pii pair<int, int>
#define F first
#define S second
#define pb push_back
const int inf = 0x3f3f3f3f;
inline int rd() {
  int x = 0, y = 1;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    if (c == '-')
      y = -1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return x * y;
}
const int N = 1.5e3 + 5, mod = 1e9 + 7;
int n, m, a[N], f[N][N], lim, pre[N], ans;
vector<int> p;
int add(int x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
  return x;
}
signed main() {
  n = rd();
  m = rd();
  lim = sqrt(m * 3) + 2; // Set a limit for efficient range traversal
  for (int i = 1; i <= n; i++)
    a[i] = rd(), pre[i] = pre[i - 1] + a[i];
  for (int i = 1; i <= n; i++)
    if (a[i])
      p.pb(i); // Store the positions of all balls
  f[0][0] = 1; // Base case: 0 balls in 0 moves
  for (int i = 1; i <= n; i++) {
    int l = max(1, pre[i] - lim), r = min({(int)p.size(), pre[i] + lim, i});
    for (int j = r; j >= l; j--) {
      int w = abs(p[j - 1] - i); // Calculate distance from previous ball position to current box
      for (int k = m; k >= w; k--)
        f[j][k] = add(f[j][k], f[j - 1][k - w]); // Transition: accumulate ways to reach current state
    }
  }
  for (int i = m; i >= 0; i -= 2)
    ans = add(ans, f[p.size()][i]); // Sum up valid results (only even k for final states)
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/