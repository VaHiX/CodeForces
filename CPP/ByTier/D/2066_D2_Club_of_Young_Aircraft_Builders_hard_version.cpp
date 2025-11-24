// Problem: CF 2066 D2 - Club of Young Aircraft Builders (hard version)
// https://codeforces.com/contest/2066/problem/D2

/*
D2. Club of Young Aircraft Builders (hard version)
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n * m * c) per test case
Space Complexity: O(n * m) per test case

This problem involves determining the number of valid ways to fill in missing floor numbers 
(0s) in an array of airplane launch records such that:
1. Each floor's perspective is respected (if c airplanes have been launched up to that point, no more from that floor).
2. The total number of airplanes launched equals m.
3. At any time, for every floor, at least c airplanes must have been launched by that time.

The approach uses dynamic programming where:
- f[i][j] represents the number of ways to fill the first i floors with exactly j airplanes.
- Preprocessing is used for combinations (C[n][k]) and cumulative counts of airplanes per floor.
- For each position, we calculate valid transitions based on constraints from the current and previous floors.

*/

#include <algorithm>
#include <stdio.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N = 105, M = 10005, P = 1e9 + 7;
int n, c, m, a[M], C[N][N], f[N][M], ct[N][M], R[N];

void Inc(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}

void solve() {
  scanf("%d%d%d", &n, &c, &m), C[0][0] = 1;
  rep(i, 1, c) {
    C[i][0] = 1;
    rep(j, 1, c) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
  }
  rep(i, 1, m) scanf("%d", &a[i]);
  rep(i, 1, n) R[i] = 0;
  rep(i, 1, m) R[a[i]] = max(R[a[i]], i); // R[i] stores latest index where floor i launched an airplane
  rep(i, 0, n + 1) rep(j, 0, m + 1) ct[i][j] = 0;
  rep(i, 1, m) ct[a[i]][i]++;
  rep(i, 1, n) rep(j, 1, m) ct[i][j] += ct[i][j - 1]; // prefix sum over columns
  rep(j, 1, m) per(i, n - 1, 1) ct[i][j] += ct[i + 1][j]; // suffix sum over rows
  rep(i, 0, n) rep(j, 0, m) f[i][j] = 0;
  f[0][0] = 1; // Base case: 0 floors, 0 airplanes
  rep(i, 1, n) rep(j, 0, m - c) if (f[i - 1][j]) {
    int r = j + c;
    if (R[i] > r)
      continue; // Not valid due to constraint violation
    int x = ct[i][r] - ct[i + 1][r], y = r - ct[i + 1][r] - j; // Calculating range of possible values
    rep(k, x, y) Inc(f[i][j + k], 1ll * f[i - 1][j] * C[y - x][k - x] % P); // DP transition with binomial coefficients
  }
  printf("%d\n", f[n][m]);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/