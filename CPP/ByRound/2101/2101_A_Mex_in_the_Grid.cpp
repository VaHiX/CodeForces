/*
 * Problem URL : https://codeforces.com/problemset/problem/2101/A
 * Submit Date : 2025-08-18
 */

#include <iostream>
using namespace std;
const int N = 505;
int a[N][N], dx[]{1, 0, -1, 0}, dy[]{0, 1, 0, -1};
void ATRI() {
  int n;
  cin >> n;
  int x = 1, y = 1, p = n * n, k = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = -1;
  while (p) {
    a[x][y] = --p;
    if (~a[x + dx[k]][y + dy[k]])
      k = (k + 1) % 4;
    x += dx[k], y += dy[k];
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cout << a[i][j] << " \n"[j == n];
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    ATRI();
  return 0;
}