/*
 * Problem URL : https://codeforces.com/problemset/problem/2101/B
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int a[maxn], wz[maxn];
void go(int x, int y) {
  swap(a[x], a[y]);
  wz[a[x]] = x, wz[a[y]] = y;
}
priority_queue<int, vector<int>, greater<int>> q[2];
void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 2; i++)
    while (!q[i].empty())
      q[i].pop();
  for (int i = 1; i <= n; i++)
    cin >> a[i], wz[a[i]] = i;
  for (int i = 1; i <= n; i++)
    q[i % 2].push(a[i]);
  for (int i = 1; i <= n - 3; i++) {
    int w = q[i % 2].top();
    q[i % 2].pop();
    //		cout<<w<<endl;
    int pos = wz[w];
    if (pos == n)
      go(pos - 2, pos), go(pos - 3, pos - 1), pos -= 2;
    go(i, pos), go(i + 1, pos + 1);
  }
  for (int i = 1; i <= n; i++)
    cout << a[i] << " ";
  cout << "\n";
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}