// Problem: CF 1921 G - Mischievous Shooter
// https://codeforces.com/contest/1921/problem/G

/*
Code Purpose: This code solves the problem of finding the maximum number of targets that can be hit by a shotgun shot on a rectangular field, where the shotgun can shoot in four diagonal directions (right-down, left-down, left-up, right-up) with a fixed Manhattan distance limit k.

Algorithms/Techniques:
- Preprocessing with prefix sums for efficient range queries
- Four rotations of the field to check all possible shooting directions
- Dynamic programming with prefix sums to count targets in each diagonal direction

Time Complexity: O(n * m) per test case, where n and m are the dimensions of the field.
Space Complexity: O(n * m) for storing the field and auxiliary arrays.

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
int n, m, k;
vector<vector<int>> a;
bool prov(int i, int j) { return 0 <= i && i < n && 0 <= j && j < m; }
int ans() {
  int cnt = 0;
  int dp[n][m];
  int pref[n][m];
  int pref_up[n][m];
  // Build prefix sums for upward direction
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pref_up[i][j] = a[i][j];
      if (prov(i - 1, j))
        pref_up[i][j] += pref_up[i - 1][j];
    }
  }
  // Build prefix sums for right direction
  for (int i = 0; i < n; i++) {
    for (int j = m - 1; j >= 0; j--) {
      pref[i][j] = a[i][j];
      if (prov(i - 1, j + 1))
        pref[i][j] += pref[i - 1][j + 1];
    }
  }
  // Calculate maximum hits for current orientation
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      dp[i][j] = pref_up[i][j];
      if (prov(i - k, j))
        dp[i][j] -= pref_up[i - k][j];
      if (prov(i, j - 1))
        dp[i][j] += dp[i][j - 1];
      if (j < k) {
        int i1 = j - k + i;
        if (i1 >= 0)
          dp[i][j] -= pref[i1][0];
      } else
        dp[i][j] -= pref[i][j - k];
      if (prov(i - k, j))
        dp[i][j] += pref[i - k][j];
      cnt = max(cnt, dp[i][j]);
    }
  }
  return cnt;
}
void solve() {
  cin >> n >> m >> k;
  k++;
  char c;
  bool st[n][m];
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(m);
  }
  // Read input and store targets
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> c;
      st[i][j] = (c == '#');
      a[i][j] = st[i][j];
    }
  }
  int mx = ans();
  // Rotate field 90 degrees clockwise
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = st[n - i - 1][j];
    }
  }
  mx = max(mx, ans());
  // Rotate field 180 degrees
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = st[i][m - j - 1];
    }
  }
  mx = max(mx, ans());
  // Rotate field 270 degrees clockwise
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = st[n - i - 1][m - j - 1];
    }
  }
  mx = max(mx, ans());
  cout << mx << '\n';
}
signed main() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios_base::sync_with_stdio(false);
  int tt;
  cin >> tt;
  while (tt--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/