/*
 * Problem URL : https://codeforces.com/problemset/problem/616/D
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 2, M = 1e6 + 2;
int a[N], cnt[M];
int tot, n, k, i, j, l, r;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  for (i = 1; i <= n; i++)
    cin >> a[i];
  for (i = j = l = r = 1; j <= n;) {
    while (j <= n && tot + !cnt[a[j]] <= k)
      tot += !(cnt[a[j++]]++);
    if (r - l < j - i)
      r = j, l = i;
    tot -= !--cnt[a[i++]];
  }
  cout << l << ' ' << r - 1 << endl;
}
