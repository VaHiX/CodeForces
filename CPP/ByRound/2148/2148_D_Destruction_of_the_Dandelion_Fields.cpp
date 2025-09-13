/*
 * Problem URL : https://codeforces.com/contest/2148/problem/D
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::sort;
int t, n, a[200005], cnt, op;
long long sum;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cnt = sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> op;
      if (op & 1)
        a[++cnt] = op;
      else
        sum += op;
    }
    if (!cnt) {
      cout << 0 << '\n';
      continue;
    }
    sort(a + 1, a + cnt + 1);
    for (int i = cnt / 2 + 1; i <= cnt; i++) {
      sum += a[i];
    }
    cout << sum << '\n';
  }
  return 0;
}
