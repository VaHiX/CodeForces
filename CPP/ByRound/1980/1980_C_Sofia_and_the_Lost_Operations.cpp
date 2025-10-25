/*
 * Problem URL : https://codeforces.com/problemset/problem/1980/C
 * Submit Date : 2025-08-12
 */

#include <bits/stdc++.h>
using namespace std;
int n, f, k, a[200005], b[200005], d[200005];
map<int, int> m;
set<int> s;
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    m.clear();
    s.clear();
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i], s.insert(b[i]);
    cin >> f;
    for (int i = 1; i <= f; i++) {
      cin >> d[i];
      m[d[i]]++;
    }
    bool ok = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i] != b[i])
        m[b[i]]--;
      if (m[b[i]] < 0)
        ok = 0;
    }
    if (s.find(d[f]) == s.end())
      ok = 0;
    if (ok)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  return 0;
}