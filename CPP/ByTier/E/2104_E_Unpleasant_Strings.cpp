/*
 * Problem URL : https://codeforces.com/problemset/problem/2104/E
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
int n, k, q, f[1000005][26], la[26], ti[1000005], dis[1000005];
string s, st[200005];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> s >> q;
  s = " " + s;
  for (int i = 0; i < k; i++) {
    f[n + 1][i] = la[i] = n + 1;
  }
  dis[n + 1] = 0;
  for (int i = n; i; i--) {
    dis[i] = 1e9;
    for (int j = 0; j < k; j++) {
      f[i][j] = la[j];
      dis[i] = min(dis[i], dis[la[j]] + 1);
    }
    la[s[i] - 'a'] = i;
  }
  for (int i = 0; i < k; i++) {
    f[0][i] = la[i];
  }
  for (int i = 1; i <= q; i++) {
    cin >> st[i];
    int fa = 0;
    for (int j = 0; j < st[i].size(); j++) {
      fa = f[fa][st[i][j] - 'a'];
    }
    cout << dis[fa] << "\n";
  }
}
