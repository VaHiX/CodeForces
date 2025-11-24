// Problem: CF 1970 B3 - Exact Neighbours (Hard)
// https://codeforces.com/contest/1970/problem/B3

/*
 * Problem: B3. Exact Neighbours (Hard)
 * 
 * Purpose:
 *   This code attempts to place n wizards' houses on an n×n grid such that:
 *   - Each wizard's house is at unique x-coordinate (column constraint)
 *   - Each wizard can visit another wizard's house exactly 'a[i]' distance away
 *   - The layout satisfies both view constraints (no house blocking view in row/column)
 * 
 * Algorithm:
 *   - Sort wizards by their required visit distance 'a[i]'
 *   - Use greedy positioning strategy for placing houses
 *   - Set up neighbor mapping (who each wizard visits)
 *   - Special handling for wizards with 0 distance requirement
 *   - Handle edge cases like n=2 which is always impossible
 * 
 * Time Complexity:
 *   O(n log n) due to sorting the wizards by required distance
 * 
 * Space Complexity:
 *   O(n) for storing arrays and pairs of coordinates
 */

#include <algorithm>
#include <iostream>
#include <utility>

#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], id[N];
int nxt[N];
pair<int, int> ans[N];

// Output the result in the required format
inline void write() {
  cout << "YES\n";
  for (int i = 1; i <= n; ++i)
    cout << ans[i].first << ' ' << ans[i].second << '\n';
  for (int i = 1; i <= n; ++i)
    cout << nxt[i] << " \n"[i == n];
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], id[i] = i;
  // Sort wizard indices by their required distance
  sort(id + 1, id + n + 1,
       [&](const int &x, const int &y) { return a[x] < a[y]; });

  // Special case: if the wizard with minimum required distance has value 0
  if (!a[id[1]]) {
    ans[id[n]] = make_pair(n, 1);  // Place the last wizard at (n, 1)
    int y = 1;
    // Position remaining wizards greedily based on distance
    for (int i = n - 1; i >= 1; --i)
      y = a[id[i + 1]] ? (y <= a[id[i + 1]] - 1 ? y + a[id[i + 1]] - 1
                                                : y - a[id[i + 1]] + 1)
                       : y,
      ans[id[i]] = make_pair(i, y), nxt[id[i + 1]] = id[i];  // Set neighbor mapping
    for (int i = 1; i <= n; ++i)
      if (!a[i])
        nxt[i] = i;  // Self-loop for wizards requiring 0 distance
    return write(), 0;
  }

  // Check for duplicate distances
  for (int p = n; p > 1; --p)
    if (a[id[p]] == a[id[p - 1]]) {
      ans[id[n]] = make_pair(n, 1);
      int y = 1;
      // Position wizards starting from p to n
      for (int i = n - 1; i >= p; --i)
        y = (y <= a[id[i + 1]] - 1 ? y + a[id[i + 1]] - 1
                                   : y - a[id[i + 1]] + 1),
        ans[id[i]] = make_pair(i, y), nxt[id[i + 1]] = id[i];
      nxt[id[p]] = id[p - 1];  // Assign neighbor for the current group
      // Handle the rest of the wizards
      for (int i = p - 1; i >= 1; --i)
        y = (y <= a[id[i]] - 1 ? y + a[id[i]] - 1 : y - a[id[i]] + 1),
        ans[id[i]] = make_pair(i, y), nxt[id[i]] = id[i + 1];
      return write(), 0;
    }

  // Edge case: n=2, no valid arrangement possible
  if (n == 2)
    return cout << "NO\n", 0;

  ans[id[n]] = make_pair(n, 1);
  int y = 1;
  // Position most distant wizards
  for (int i = n - 1; i >= 3; --i)
    y = (y <= a[id[i + 1]] - 1 ? y + a[id[i + 1]] - 1 : y - a[id[i + 1]] + 1),
    ans[id[i]] = make_pair(i, y), nxt[id[i + 1]] = id[i];
  // Position the last two wizards
  ans[id[2]] = make_pair(1, y > 1 ? y - 1 : y + 1), nxt[id[3]] = id[2];
  ans[id[1]] = make_pair(2, y), nxt[id[2]] = id[1];
  nxt[id[1]] = id[3];
  return write(), 0;
}


// https://github.com/VaHiX/CodeForces/