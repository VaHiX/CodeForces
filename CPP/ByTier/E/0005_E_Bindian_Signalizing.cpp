/*
 * Problem URL : https://codeforces.com/problemset/problem/5/E
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>
using namespace std;

int n, a[1000010], id, s[1000010], cnt[1000010], t;
long long ans;
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i), a[i] > a[id] && (id = i);
  rotate(a + 1, a + id, a + n + 1);
  for (int i = 2; i <= n; ++i) {
    while (s[t] < a[i] && t)
      ans += cnt[t--];
    if (s[t] != a[i])
      s[++t] = a[i], cnt[t] = 0;
    ans += cnt[t]++;
  }
  while (t > 1)
    ans += cnt[t--];
  cout << ans + n - 1 << endl;
  return 0;
}