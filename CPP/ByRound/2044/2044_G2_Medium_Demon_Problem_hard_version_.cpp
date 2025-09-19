/*
 * Problem URL : https://codeforces.com/contest/2044/problem/G2
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define end '\n'
void sol() {
  int n;
  cin >> n;
  int ans = 0;
  vector<int> ind(n + 1, 0);
  vector<int> d(n + 1, 0);
  vector<int> nxt(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    cin >> nxt[i];
    d[i]++;
    ind[nxt[i]]++;
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (!ind[i])
      q.push(i);
  }
  while (!q.empty()) {
    auto u = q.front();
    auto v = nxt[u];
    q.pop();
    ans = max(ans, d[u]);
    ind[v]--;
    d[v] += d[u];
    if (!ind[v])
      q.push(v);
  }
  cout << ans + 2 << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    sol();
  }
  return 0;
}