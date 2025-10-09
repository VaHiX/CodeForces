/*
 * Problem URL : https://codeforces.com/contest/1383/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, ans = 0;
  string s, t;
  cin >> n >> s >> t;
  vector<vector<int>> b(26, vector<int>(26));
  for (int i = 0; i < n; i++)
    if (s[i] > t[i]) {
      cout << "-1\n";
      return;
    } else
      b[s[i] - 'a'][t[i] - 'a'] = 1;
  for (int i = 0; i < 26; i++) {
    int j = i + 1;
    while (j < 26 && !b[i][j])
      j++;
    if (j < 26) {
      ans++;
      for (int k = i; k < 26; k++)
        if (b[i][k])
          b[j][k] = 1;
    }
  }
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