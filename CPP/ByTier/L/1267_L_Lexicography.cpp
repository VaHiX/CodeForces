/*
 * Problem URL : https://codeforces.com/contest/1267/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long
char a[1005][1005];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m, k, tot = 0;
  string s;
  cin >> n >> m >> k >> s;
  sort(s.begin(), s.end());

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < k; j++) {
      if (a[j][i - 1] == a[k - 1][i - 1])
        a[j][i] = s[tot++];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 0)
        a[i][j] = s[tot++];
    }
  }

  for (int i = 0; i < n; i++)
    cout << a[i] + 1 << '\n';
}