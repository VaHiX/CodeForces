/*
 * Problem URL : https://codeforces.com/contest/434/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
int a[100005];
vector<int> v[100005];
inline int D(int x, int y) { return max(x, y) - min(x, y); }
inline int cal(int x) {
  vector<int> s;
  for (auto t : v[x]) {
    if (t - 1 > 0 && a[t - 1] != a[t])
      s.push_back(a[t - 1]);
    if (t + 1 <= m && a[t + 1] != a[t])
      s.push_back(a[t + 1]);
  }
  if (s.empty())
    return 0;
  int qwq = 0;
  for (auto t : s)
    qwq += D(x, t);
  sort(s.begin(), s.end());
  int k = s[s.size() / 2];
  for (auto t : s)
    qwq -= D(k, t);
  return qwq;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
    v[a[i]].push_back(i);
  }
  for (int i = 2; i <= m; i++)
    ans += D(a[i], a[i - 1]);
  int mx = 0;
  for (int i = 1; i <= n; i++)
    mx = max(mx, cal(i));
  cout << ans - mx;
  return 0;
}