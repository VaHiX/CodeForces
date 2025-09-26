/*
 * Problem URL : https://codeforces.com/contest/1424/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;

int n, k;
char s[1000005][105];
int f[26][26];
void cpr(char *s, char *t) {
  int n = strlen(s), m = strlen(t);
  for (int i = 0; i < min(n, m); i++) {
    if (s[i] != t[i]) {
      f[s[i] - 'a'][t[i] - 'a'] = 1;

      return;
    }
  }
  if (n < m) {
    cout << "IMPOSSIBLE";
    exit(0);
  }
}
bool vis[27];
bool flg;
int cnt;
bool sk[27];
char ans[27];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    for (int j = p * k + 1; j <= (p + 1) * k; j++) {
      cin >> s[j];
      int len = strlen(s[j]);
      for (int aa = 0; aa < len; aa++)
        vis[s[j][aa] - 'a'] = 1;
    }
  }
  for (int i = 2; i <= n * k; i++) {
    cpr(s[i], s[i - 1]);
  }
  for (int k = 0; k < 26; k++) // Floyd 求传递闭包
    for (int i = 0; i < 26; i++)
      for (int j = 0; j < 26; j++)
        f[i][j] |= f[i][k] & f[k][j];
  for (int i = 0; i < 26; i++)
    flg |= f[i][i];
  if (flg) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  for (int i = 0; i < 26; i++)
    cnt += vis[i];
  for (int i = 1; i <= cnt; i++) {
    char c;
    for (int j = 0; j < 26; j++) {
      if (vis[j] and !sk[j]) {
        int p = 0;
        for (int k = 0; k < 26; k++) {
          p |= (!sk[k] and f[j][k]);
        }
        if (!p) {
          c = j + 'a';
          break;
        }
      }
    }
    sk[c - 'a'] = 1;
    ans[i - 1] = c;
  }
  cout << ans;
}