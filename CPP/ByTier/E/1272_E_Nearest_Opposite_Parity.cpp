/*
 * Problem URL : https://codeforces.com/problemset/problem/1272/E
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> g[200001];
int a[200001], d[200001];
int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    d[i] = -1;
    if (i > a[i])
      g[i - a[i]].emplace_back(i);
    if (i + a[i] <= n)
      g[i + a[i]].emplace_back(i);
  }
  queue<int> q;
  for (int i = 1; i <= n; i++)
    for (int j : g[i])
      if ((a[i] ^ a[j]) & 1)
        q.emplace(j), d[j] = 1;
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (int i : g[t])
      if (d[i] == -1)
        d[i] = d[t] + 1, q.emplace(i);
  }
  for (int i = 1; i <= n; i++)
    cout << d[i] << ' ';
  cout << endl;
  return 0;
}