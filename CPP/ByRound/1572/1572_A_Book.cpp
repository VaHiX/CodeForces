/*
 * Problem URL : https://codeforces.com/contest/1572/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, ans = 0;
  cin >> n;
  vector<int> d(n), f(n, 1);
  vector<vector<int>> e(n);
  queue<int> q;
  for (int i = 0; i < n; i++) {
    cin >> d[i];
    for (int j = 0, x; j < d[i]; j++)
      cin >> x, e[x - 1].push_back(i);
    if (!d[i])
      q.push(i);
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    ans = max(ans, f[x]);
    for (int y : e[x]) {
      f[y] = max(f[y], f[x] + (x > y));
      if (!--d[y])
        q.push(y);
    }
  }

  if (count(begin(d), end(d), 0) != n)
    cout << "-1\n";
  else
    cout << ans << "\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}