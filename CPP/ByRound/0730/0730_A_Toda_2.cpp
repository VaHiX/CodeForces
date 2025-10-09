/*
 * Problem URL : https://codeforces.com/contest/730/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
struct num {
  int x, id;
  operator int() const { return x; }
} r[201];
int n, f[20001][201];
int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> r[i].x, r[i].id = i;
  sort(r, r + n);
  int ans = 0;
  for (; r[0].x != r[n - 1].x; ans++) {
    int c = 0;
    for (int i = n - 1; i >= 0; i--)
      if (r[i].x == r[n - 1].x)
        c++;
    if (c == 1)
      c = 2;
    if (c > 5)
      c = min(5, c - 2);
    for (int i = n - 1; i >= n - c; i--) {
      if (r[i].x)
        r[i].x--;
      f[ans][r[i].id] = 1;
    }
    sort(r, r + n);
  }
  cout << r[0].x << '\n' << ans << '\n';
  for (int i = 0; i < ans; i++, cout << '\n')
    for (int j = 0; j < n; j++)
      cout << f[i][j];
}
