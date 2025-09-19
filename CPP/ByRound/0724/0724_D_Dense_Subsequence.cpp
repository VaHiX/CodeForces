/*
 * Problem URL : https://codeforces.com/contest/724/problem/D
 * Submit Date : 2025-09-13
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int, int>
using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int m;
  cin >> m;
  string s;
  cin >> s;
  vector<char> a;
  vector<int> used(s.size());
  int p = 0;
  char mx = 'a';
  while (p + m <= s.size()) {
    int mn = p;
    for (int i = p; i < p + m; i++) {
      if (s[mn] >= s[i])
        mn = i;
    }
    a.pb(s[mn]);
    mx = max(mx, s[mn]);
    p = mn + 1;
    used[mn] = 1;
  }
  for (int i = 0; i < s.size(); i++)
    if (!used[i] && s[i] < mx)
      a.pb(s[i]);
  sort(a.begin(), a.end());
  for (int i = 0; i < a.size(); i++)
    cout << a[i];
  return 0;
}
