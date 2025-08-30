/*
 * Problem URL : https://codeforces.com/problemset/problem/2052/J
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
long long int t, n, m, q, e[200005], now, tot;
pair<long long int, long long int> task[200005];
vector<long long int> v;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i)
      cin >> task[i].second;
    for (int i = 0; i < n; ++i)
      cin >> task[i].first;
    for (int i = 0; i < m; ++i)
      cin >> e[i];
    sort(task, task + n);
    now = 1e18;
    for (int i = n - 1; i >= 0; --i) {
      now = min(now, task[i].first);
      task[i] = make_pair(now - task[i].second + 1, now);
      now = task[i].first - 1;
    }
    v.clear();
    v.push_back(0);
    now = 1, tot = 0;
    task[n] = make_pair(1e18, 1e18);
    for (int i = 0; i < m; ++i) {
      while (now + e[i] > task[tot].first)
        now += task[tot].second - task[tot].first + 1, ++tot;
      now += e[i];
      v.push_back(now - 1);
    }
    while (q--) {
      long long int tk;
      cin >> tk;
      int l = 0, r = m, mid;
      while (l < r) {
        mid = l + r + 1 >> 1;
        if (v[mid] <= tk)
          l = mid;
        else
          r = mid - 1;
      }
      cout << l << ' ';
    }
    cout << '\n';
  }
  return 0;
}