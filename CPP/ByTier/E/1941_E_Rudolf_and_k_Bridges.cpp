// Problem: CF 1941 E - Rudolf and k Bridges
// https://codeforces.com/contest/1941/problem/E

/*
Code Purpose:
This code solves the problem of minimizing the total cost of building k bridges across a river grid. 
Each bridge is built on a consecutive set of rows, and supports must be placed so that adjacent supports
are within a given distance d. The cost of placing a support is the depth of the cell plus 1.

Approach:
1. For each row, compute the minimum cost to build a bridge across that row using a sliding window technique with a deque.
2. Use prefix sums to quickly calculate the total cost for k consecutive rows.
3. Find the minimum among all possible consecutive k-row combinations.

Algorithms/Techniques:
- Sliding window with deque for efficient minimum cost calculation in each row.
- Prefix sum technique to optimize k-row cost computation.
- Dynamic programming concept to compute minimum support cost for each row.

Time Complexity: O(n * m)
Space Complexity: O(m)
*/

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

#define int long long
#define endl "\n"
using namespace std;
const int N = 2e5 + 10;
int t;
int a[N];
int f[N];
void solve() {
  int n, m, k, d;
  cin >> n >> m >> k >> d;
  vector<long long> s;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      cin >> a[j];
    deque<int> q;
    q.push_back(1);
    f[1] = 1; // Cost of support at first cell (always 1 since it's the minimum requirement)
    for (int j = 2; j <= m; j++) {
      // Remove elements from front that are out of distance range
      while (!q.empty() && j - q.front() - 1 > d)
        q.pop_front();
      // Calculate minimum cost to place support at position j
      f[j] = f[q.front()] + a[j] + 1;
      // Maintain deque in increasing order of f values (monotonic deque)
      while (!q.empty() && f[j] <= f[q.back()])
        q.pop_back();
      q.push_back(j);
    }
    s.push_back(f[m]); // Store the minimum cost for this row
  }
  int ans = 1e18;
  // Compute prefix sums
  for (int i = 1; i < n; i++)
    s[i] += s[i - 1];
  // Find minimum sum for k consecutive rows
  ans = min(ans, s[k - 1]);
  for (int i = 1; i + k - 1 < n; i++)
    ans = min(ans, s[i + k - 1] - s[i - 1]);
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/