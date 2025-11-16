// Problem: CF 1868 E - Min-Sum-Max
// https://codeforces.com/contest/1868/problem/E

/*
Algorithm: Dynamic Programming with Coordinate Compression
Time Complexity: O(n^3 * log n) where n is the size of array
Space Complexity: O(n^3) for the 3D DP table

The problem is to partition an array into maximum number of contiguous subsegments
such that for every pair of subsegments, the sum of one subsegment is between
the minimum and maximum sum of the pair of subsegments.

Approach:
1. Use coordinate compression to reduce the range of prefix sums.
2. Define f[l][r][k] = maximum number of segments in subarray [l, r] if the sum of
   the first segment is k.
3. Use dynamic programming to compute the maximum segments possible.
4. Additionally, check transitions when splitting the array at a point.
*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const long long MAXN = 4e5 + 10, MAXM = 3e2 + 10;
long long n;
long long a[MAXN], tmp[MAXN], m;
long long f[MAXM][MAXM][MAXM];
bool in(long long x, long long l, long long r) {
  if (l > r)
    swap(l, r);
  return l <= x && x <= r;
}
void chkmax(long long &x, long long y) { x = max(x, y); }
void work() {
  cin >> n;
  for (long long i = 1; i <= n; i++)
    cin >> a[i], a[i] += a[i - 1]; // prefix sum
  for (long long i = 0; i <= n; i++)
    tmp[i] = a[i];
  sort(tmp, tmp + n + 1);
  m = unique(tmp, tmp + n + 1) - tmp; // coordinate compression
  for (long long i = 0; i <= n; i++)
    a[i] = lower_bound(tmp, tmp + m, a[i]) - tmp + 1;
  // Initialize DP
  for (long long i = 0; i <= n; i++)
    for (long long j = 0; j <= n; j++)
      for (long long k = 1; k <= m; k++)
        f[i][j][k] = -1e9;
  for (long long i = 0; i <= n; i++)
    for (long long j = 1; j <= m; j++)
      f[i][i][j] = 1; // base case: single element = 1 segment
  // DP transitions
  for (long long len = 2; len <= n + 1; len++)
    for (long long l = 0, r = len - 1; r <= n; ++l, ++r) {
      long long lst = -1;
      for (long long i = l; i <= r - 1; i++) {
        if (a[i] == a[l])
          lst = i;
        if (lst != -1 && in(a[r], a[l], a[i + 1]))
          chkmax(f[l][r][a[i + 1]], f[l][lst][a[i + 1]] + f[i + 1][r][a[l]]);
      }
      lst = -1;
      for (long long i = l; i <= r - 1; i++) {
        if (a[i] == a[r])
          lst = i;
        if (lst != -1 && in(a[l], a[r], a[i + 1]))
          chkmax(f[l][r][a[i + 1]], f[l][lst][a[i + 1]] + f[i + 1][r][a[r]]);
      }
      lst = -1;
      for (long long i = r; i >= l + 1; i--) {
        if (a[i] == a[l])
          lst = i;
        if (lst != -1 && in(a[r], a[l], a[i - 1]))
          chkmax(f[l][r][a[i - 1]], f[l][i - 1][a[l]] + f[lst][r][a[i - 1]]);
      }
      lst = -1;
      for (long long i = r; i >= l + 1; i--) {
        if (a[i] == a[r])
          lst = i;
        if (lst != -1 && in(a[l], a[r], a[i - 1]))
          chkmax(f[l][r][a[i - 1]], f[l][i - 1][a[r]] + f[lst][r][a[i - 1]]);
      }
      // Propagate bounds
      for (long long i = min(a[l], a[r]); i >= 2; i--)
        chkmax(f[l][r][i - 1], f[l][r][i]);
      for (long long i = max(a[l], a[r]); i <= m - 1; i++)
        chkmax(f[l][r][i + 1], f[l][r][i]);
    }
  long long res = 0;
  for (long long i = 1; i <= m; i++)
    res = max(res, f[0][n][i]);
  // Check boundary splits
  for (long long i = 1; i <= n; i++)
    for (long long j = i + 1; j <= n - 1; j++) {
      if (in(a[0], a[i], a[j]) && in(a[n], a[i], a[j])) {
        res = max(res, f[0][i][a[j]] + f[j][n][a[i]]);
      }
    }
  cout << res - 1 << endl; // subtract 1 to match segment count
}
int main() {
  long long T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/