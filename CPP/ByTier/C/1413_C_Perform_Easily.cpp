/*
 * Problem URL : https://codeforces.com/problemset/problem/1413/C
 * Submit Date : 2025-08-13
 */

#include <algorithm>
#include <iostream>
using namespace std;
int a[10], na, n, b[100500], ans, minn;
int main() {
  ios::sync_with_stdio(false);
  na = 6;
  for (int i = 0; i < 6; i++)
    cin >> a[i];
  sort(a, a + na);
  na = unique(a, a + na) - a;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> b[i];
  sort(b, b + n);
  ans = -1;
  n = unique(b, b + n) - b;
  for (int k = 0; k < na; k++)
    for (int i = 0; i < n; i++) {
      if (i != n - 1 && b[n - 1] - a[na - 1] > b[i] - a[k])
        continue;
      minn = b[i] - a[k];
      for (int r = 0, cur = 0; r < na; r++) {
        if (b[i] - a[k] < b[0] - a[r])
          continue;
        minn = min(minn, b[cur] - a[r]);
        cur = upper_bound(b + cur, b + n, b[i] - a[k] + a[r]) - b;
        if (cur == n)
          break;
      }
      if (ans == -1)
        ans = b[i] - a[k] - minn;
      else
        ans = min(ans, b[i] - a[k] - minn);
    }
  cout << ans << endl;
  return 0;
}