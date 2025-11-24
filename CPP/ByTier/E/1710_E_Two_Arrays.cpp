// Problem: CF 1710 E - Two Arrays
// https://codeforces.com/contest/1710/problem/E

/*
Algorithm: Binary search on answer with a custom checker function.
Techniques: 
- Binary search over the possible score values.
- For each candidate score, determine if it's achievable by analyzing the game using a greedy-like approach.
- Preprocessing arrays by sorting them to optimize the search.
- Tracking visited counts implicitly via the number of valid moves and the structure of the game.

Time Complexity: O((n + m) * log(max_score)) where max_score is bounded by 10^17.
Space Complexity: O(n + m) for storing the arrays and auxiliary variables.

The solution uses binary search on the answer, and for each candidate answer,
it checks whether that score can be achieved considering the game dynamics:
- Alice wants to minimize, Bob wants to maximize.
- The game ends when someone moves the rook to a cell (r, c) such that
  a[r] + b[c] equals the current score.
- The key insight is that the optimal path depends on how many times we can
  traverse the grid, taking into account the visit limits.
*/
#include <algorithm>
#include <iostream>

using namespace std;
enum { N = 200009 };
int n, m, a[N], b[N], pa, pb;
bool chk(int o) {
  long long now = 0, mx = 0, mx2 = 0;
  int i = n - 1, j = m, y = 0, x = 0;
  // Advance x until a[x+1] + b[j] >= o, to find the minimum x for valid cells
  while (x < n && a[x + 1] + b[j] < o)
    ++x;
  // Iterate from bottom to top (i from n-1 down to 0)
  for (; ~i; --i) {
    // Advance y until a[i+1] + b[y+1] >= o, to find valid column indices
    while (y < m && a[i + 1] + b[y + 1] < o)
      ++y;
    // Add the number of valid columns (from y to m-1) for current row
    now += m - y - j;
    // For each column j, update the current valid number of moves and possibly update x
    while (j && n - x - i > 0) {
      now += n - x - i, --j;
      if (j)
        while (x < n && a[x + 1] + b[j] < o)
          ++x;
    }
    // Track maximum number of moves up to row i
    mx = max(mx, now);
    // Track if we are in the path that includes start position a[1] and b[1]
    if (pa <= i || pb <= j)
      mx2 = max(mx2, now);
  }
  // Return true if the maximum moves in the path is different from a special case
  return mx != mx2;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int i;
  cin >> n >> m;
  for (i = 1; i <= n; ++i)
    cin >> a[i];
  for (i = 1; i <= m; ++i)
    cin >> b[i];
  int a1 = a[1], b1 = b[1], l = 1, r = a1 + b1, x;
  sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
  pa = lower_bound(a + 1, a + n + 1, a1) - a,
  pb = lower_bound(b + 1, b + m + 1, b1) - b;
  while (l < r) {
    x = (l + r + 1) >> 1;
    if (chk(x))
      l = x;
    else
      r = x - 1;
  }
  cout << l;
}


// https://github.com/VaHiX/CodeForces/