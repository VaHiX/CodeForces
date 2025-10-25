// Problem: CF 1890 E2 - Doremy's Drying Plan (Hard Version)
// https://codeforces.com/contest/1890/problem/E2

/*
Algorithm: Dynamic Programming with Segment Optimization
Time Complexity: O(n * k^2 * m), where n is number of cities, k is max days to prevent, m is number of days
Space Complexity: O(n * k), for DP arrays

The problem involves selecting k out of m days to prevent rain such that the number of dry cities is maximized.
A city is dry if it never gets rain on any of the m days.
We use dynamic programming where F[i][j] represents the maximum number of dry cities 
by considering up to city i and using j days from the first i days to prevent rain.

The approach uses a sweep line technique with segment optimization to compute all combinations efficiently.
*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
#define ii pair<int, int>
#define fi first
#define se second
const int MAXN = 2e5 + 5;
int F[11][MAXN], A[15][15], B[15][420], C[15][420], cnt[15], c2[15];
bool sortt(ii a, ii b) {
  if (a.fi == b.fi)
    return a.se > b.se;
  return a.fi < b.fi;
}
ii val[MAXN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
      cin >> val[i].fi >> val[i].se;
    sort(val + 1, val + m + 1, sortt);
    int l = 1, ans = 0;
    for (int j = 0; j <= k; j++)
      c2[j] = cnt[j] = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= k; j++)
        F[j][i] = -1e9;
    F[0][0] = 0, c2[0] = 1, A[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      int r = l;
      while (r <= m && val[r].fi == i)
        r++;
      r--;
      for (int j = l; j <= r; j++)
        for (int p = k; p + 1; p--)
          if (p - (j - l) >= 0)
            for (int q = 0; q < c2[p - (j - l)]; q++)
              B[p][cnt[p]] = max(A[p - (j - l)][q], val[j].se),
              C[p][cnt[p]] = F[p - (j - l)][A[p - (j - l)][q]] +
                             max(0, val[j].fi - A[p - (j - l)][q] - 1) *
                                 (A[p - (j - l)][q] <= val[j].se),
              cnt[p]++;
      for (int p = k; p + 1; p--)
        if (p - (r - l + 1) >= 0)
          for (int q = 0; q < c2[p - (r - l + 1)]; q++)
            B[p][cnt[p]] = max(A[p - (r - l + 1)][q], i),
            C[p][cnt[p]] = F[p - (r - l + 1)][A[p - (r - l + 1)][q]] +
                           max(0, i - A[p - (r - l + 1)][q]) *
                               (A[p - (r - l + 1)][q] <= i),
            cnt[p]++;
      for (int p = k; p + 1; p--) {
        for (int j = 0; j < c2[p]; j++)
          F[p][A[p][j]] = -1e9;
        c2[p] = 0;
        for (int j = 0; j < cnt[p]; j++)
          if (F[p][B[p][j]] == -1e9)
            F[p][B[p][j]] = C[p][j], A[p][c2[p]++] = B[p][j];
          else
            F[p][B[p][j]] = max(F[p][B[p][j]], C[p][j]);
        cnt[p] = 0;
      }
      l = r + 1;
    }
    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= k; j++)
        ans = max(ans, F[j][i]);
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/