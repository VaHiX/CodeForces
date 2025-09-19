/*
 * Problem URL : https://codeforces.com/problemset/problem/2094/G
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, q;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> q;
    int op, x, cnt = 0, ans[2] = {0}, s = 0;
    deque<int> d[2];
    while (q--) {
      cin >> op;
      if (op == 1) {
        int si = d[cnt].size(), tmp = d[cnt].back();
        d[cnt].pop_back();
        d[cnt].push_front(tmp);
        ans[cnt] += s - 1ll * si * tmp;
        d[cnt ^ 1].pop_front();
        d[cnt ^ 1].push_back(tmp);
        ans[cnt ^ 1] += 1ll * si * tmp - s;
      }
      if (op == 2)
        cnt ^= 1;
      if (op == 3) {
        cin >> x;
        d[cnt].push_back(x);
        s += x;
        ans[cnt] += 1ll * d[cnt].size() * x;
        d[cnt ^ 1].push_front(x);
        ans[cnt ^ 1] += s;
      }
      cout << ans[cnt] << "\n";
    }
  }

  return 0;
}