/*
 * Problem URL : https://codeforces.com/problemset/problem/2085/F2
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000100
int t, n, k, val[N], pre[N], del[N];
int work() {
  for (int i = 1; i <= n; ++i)
    pre[i] = del[i] = 0;

  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    if (pre[val[i]] == 0)
      sum += i - 1;
    else
      del[(pre[val[i]] + i) / 2]--, del[(pre[val[i]] + i + 1) / 2]--;
    del[i] += 2;
    pre[val[i]] = i;
  }

  int ans = 1e18, dis = -k;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, sum), dis += del[i], sum += dis;
  for (int i = 1; i <= k; ++i)
    ans -= abs((k + 1) / 2 - i);
  return ans;
}
signed main() {
  ios::sync_with_stdio(false);

  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
      cin >> val[i];
    cout << work() << endl;
  }

  return 0;
}