/*
 * Problem URL : https://codeforces.com/problemset/problem/1277/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  string s;
  cin >> t;
  while (t--) {
    cin >> s;
    vector<int> v;
    for (string t : {"twone", "one", "two"}) {
      for (size_t p = 0; (p = s.find(t, p)) != string::npos;) {
        s[p + t.size() / 2] = ' ';
        v.push_back(p + t.size() / 2);
      }
    }
    cout << v.size() << '\n';
    for (auto i : v)
      cout << i + 1 << ' ';
    cout << '\n';
  }
  return 0;
}