/*
 * Problem URL : https://codeforces.com/problemset/problem/2059/E1
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int a[N], b[N];

void solve() {

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n * m; i++)
    cin >> a[i];
  for (int i = 0; i < n * m; i++)
    cin >> b[i];

  int pa = 0, pb = 0, flag = 1, ans = n * m;
  while (flag) {
    while (pb != n * m && b[pb] != a[pa])
      pb++;
    if (pb == n * m)
      break;
    if (pa / m == pb / m) {
      pa++, pb++;
      while (pa % m != 0 && pa / m == pb / m) {
        if (a[pa] != b[pb]) {
          flag = 0;
          break;
        }
        pa++, pb++;
      }
    } else {
      pa++, pb++;
    }
    if (flag)
      ans = n * m - pa;
  }
  cout << ans << endl;

  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int _;
  cin >> _;
  while (_--)
    solve();

  return 0;
}