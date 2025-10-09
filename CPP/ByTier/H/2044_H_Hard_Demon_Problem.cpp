/*
 * Problem URL : https://codeforces.com/contest/2044/problem/H
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
long long origin[2001][2001] = {0};
long long xsum[2001][2001] = {0}, ysum[2001][2001] = {0};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int temp;
        cin >> temp;
        origin[i][j] =
            origin[i - 1][j] + origin[i][j - 1] - origin[i - 1][j - 1] + temp;
        xsum[i][j] =
            xsum[i - 1][j] + xsum[i][j - 1] - xsum[i - 1][j - 1] + i * temp;
        ysum[i][j] =
            ysum[i - 1][j] + ysum[i][j - 1] - ysum[i - 1][j - 1] + j * temp;
      }
    }
    while (q--) {
      int x1, x2, y1, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      long long count = 0;
      long long sumxy = origin[x2][y2] - origin[x1 - 1][y2] -
                        origin[x2][y1 - 1] + origin[x1 - 1][y1 - 1];
      count += sumxy;
      count += ysum[x2][y2] - ysum[x1 - 1][y2] - ysum[x2][y1 - 1] +
               ysum[x1 - 1][y1 - 1] - sumxy * y1;
      count +=
          (y2 - y1 + 1) * (xsum[x2][y2] - xsum[x1 - 1][y2] - xsum[x2][y1 - 1] +
                           xsum[x1 - 1][y1 - 1] - sumxy * x1);
      cout << count << ' ';
    }
    cout << endl;
  }
  return 0;
}
