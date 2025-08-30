/*
 * Problem URL : https://codeforces.com/problemset/problem/2107/C
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, m, k, sum, cnt, pre, a[N], b[N], d[N];
string c;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int i, j, x, y, z, t;
  cin >> t;
  while (t--) {
    cin >> n >> k >> c;
    for (i = 0; i < n; i++)
      cin >> a[i];
    pre = -1, sum = cnt = 0;
    for (i = 0; i < n; i++) {
      if (c[i] == '0')
        pre = i, a[i] = INT_MIN;
      cnt = max(cnt + a[i], a[i]), sum = max(sum, cnt);
    }
    if (sum > k || (sum != k && pre == -1))
      cout << "No\n";
    else {
      if (pre != -1) {
        sum = cnt = 0;
        for (i = pre + 1; i < n; i++)
          cnt += a[i], sum = max(sum, cnt);
        k -= sum, sum = cnt = 0;
        for (i = pre - 1; i >= 0; i--)
          cnt += a[i], sum = max(sum, cnt);
        a[pre] = k - sum;
      }
      cout << "Yes\n";
      for (i = 0; i < n; i++)
        cout << a[i] << " ";
      cout << "\n";
    }
  }
  return 0;
}