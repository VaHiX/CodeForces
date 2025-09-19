/*
 * Problem URL : https://codeforces.com/contest/2029/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 1e6 + 10;
int n, ans;
string s;
signed _main() {
  //	ios::sync_with_stdio(false);
  //	cin.tie(0);cout.tie(0);
  cin >> n >> s;
  //	if(s=="0") exit(0);
  int t = 0;
  while (s[t] == s[0]) {
    ++t;
    if (t == n) {
      cout << "YES\n";
      return 0;
    }
  }
  bool fl1 = 0, fl2 = 0, fl = 0;
  int i = 0, tot = 0;
  while (i < n) {
    ++tot;
    int lst = (i + t) % n, len = 0;
    while (s[(i + t) % n] == s[lst])
      ++i, ++len;
    //		cout<<lst<<' '<<i<<' '<<len<<'\n';
    if (len > 1) {
      if (s[lst] == 'R')
        fl1 = 1;
      else
        fl2 = 1;
      if (fl1 & fl2) {
        cout << "NO\n";
        return 0;
      }
    }
    if (len % 2 == 0) {
      if (fl) {
        cout << "NO\n";
        return 0;
      }
      fl = 1;
    }
  }
  if (fl || tot == 2)
    cout << "YES\n";
  else
    cout << "NO\n";
  return 0;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    _main();
  return 0;
}