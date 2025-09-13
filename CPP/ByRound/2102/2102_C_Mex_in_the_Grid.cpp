/*
 * Problem URL : https://codeforces.com/problemset/problem/2102/C
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define N 505
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, i, j, a[N][N], x;
  int di[4] = {0, 1, 0, -1}, dj[4] = {1, 0, -1, 0}, d;
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
        a[i][j] = -1;
    x = n * n - 1;
    i = j = 1;
    d = 0;
    while (x >= 0) {
      a[i][j] = x;
      x--;
      if (i + di[d] > n || i + di[d] < 1 || j + dj[d] > n || j + dj[d] < 1 ||
          a[i + di[d]][j + dj[d]] != -1)
        d = (d + 1) % 4;
      i = i + di[d];
      j = j + dj[d];
    }
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++)
        cout << a[i][j] << ' ';
      cout << '\n';
    }
  }
  return 0;
}
