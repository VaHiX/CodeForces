/*
 * Problem URL : https://codeforces.com/problemset/problem/221/D
 * Submit Date : 2025-08-13
 */

/*
 *  In the name of God
 *
 *  Author: Farbod Doost
 *  Last Modified: Sat, 05 Nov 2022 (15:50:00)
 *
 */
#include <iostream>
using namespace std;

const int N = 1e5 + 5, sq = 350;

int n, a[N], cnt[N], l[N], r[N], pre[N], ans[N];

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    cin >> a[i];

    if (a[i] <= n)
      cnt[a[i]]++;
  }

  for (int i = 0; i < q; i++)
    cin >> l[i] >> r[i], l[i]--, r[i]--;

  for (int i = 1; i <= n; i++) {
    if (cnt[i] < i)
      continue;

    for (int j = 1; j <= n; j++)
      pre[j] = pre[j - 1] + (a[j - 1] == i);
    for (int j = 0; j < q; j++)
      ans[j] += (pre[r[j] + 1] - pre[l[j]] == i);
  }

  for (int i = 0; i < q; i++)
    cout << ans[i] << '\n';

  return 0;
}
