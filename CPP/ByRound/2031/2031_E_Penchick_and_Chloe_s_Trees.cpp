/*
 * Problem URL : https://codeforces.com/contest/2031/problem/E
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 2;
int T, n, f[N];
vector<int> e[N];
priority_queue<int, vector<int>, greater<int>> q;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    for (int i = 2, x; i <= n; ++i)
      cin >> x, e[x].push_back(i);
    for (int i = n; i; --i) {
      if (!e[i].size()) {
        f[i] = 0;
        continue;
      }
      for (int v : e[i])
        q.push(f[v]);
      for (int x; q.size() > 1;) {
        q.pop();
        x = q.top(), q.pop();
        q.push(x + 1);
      }
      f[i] = q.top() + (e[i].size() == 1), q.pop();
      e[i].clear();
    }
    cout << f[1] << '\n';
  }
  return 0;
}
