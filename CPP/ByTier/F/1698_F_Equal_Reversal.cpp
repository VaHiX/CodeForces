// Problem: CF 1698 F - Equal Reversal
// https://codeforces.com/contest/1698/problem/F

/*
Algorithm: 
- The approach attempts to transform array 'a' into array 'b' by performing a series of reverse operations.
- The core idea is to fix elements one by one from the beginning, using a greedy method to make necessary swaps.
- The algorithm uses a helper function 'solve' to handle individual element placements.
- Special care is taken to ensure that the first and last elements match between arrays 'a' and 'b' in the initial check.

Time Complexity: O(n^3) in the worst case, because for each position, we may need to perform nested loops to find and apply reversals.
Space Complexity: O(n^2) for storing the operations (in worst case, when n^2 operations are needed).

Techniques:
- Greedy algorithm with backtracking.
- Simulation of array reversals using reverse() function.
- Handling of edge cases and initial mismatches.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int i, j, k, n, m, t, a[505], b[505];
vector<pair<int, int>> op;
#define F(X, Y)                                                                \
  op.push_back({X, Y});                                                        \
  reverse(a + X, a + Y + 1);                                                   \
  return 1;
bool solve(int x) {
  int i, j, k, xy = 0;
  for (i = x; i <= n; i++) {
    if (a[i - 1] == b[x - 1] && a[i] == b[x] && !xy)
      xy = i;
    if (a[i - 1] == b[x] && a[i] == b[x - 1]) {
      x--;
      F(x, i);
    }
  }
  if (xy)
    for (i = xy - 1; i >= x; i--)
      for (j = xy; j <= n; j++)
        if (a[i] == a[j]) {
          F(i, j);
        }
  return 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    int cnt = 0;
    cin >> n;
    op.clear();
    for (i = 1; i <= n; i++)
      cin >> a[i];
    for (i = 1; i <= n; i++)
      cin >> b[i];
    if (a[1] != b[1] || a[n] != b[n]) {
      cout << "NO\n";
      continue;
    }
  aa:;
    cnt++;
    if (cnt > n * n) {
      cout << "NO\n";
      continue;
    }
    for (i = 2; i < n; i++)
      if (a[i] != b[i]) {
        if (solve(i)) {
          goto aa;
        } else {
          cout << "NO\n";
          goto aaa;
        }
      }
    cout << "YES\n" << op.size() << '\n';
    for (auto [x, y] : op)
      cout << x << ' ' << y << '\n';
  aaa:;
  }
}


// https://github.com/VaHiX/CodeForces/