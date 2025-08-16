/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>

using namespace std;

map<int, pair<int, int>> m;
int t, n;

int main() {
  cin >> t;
  while (t--) {
    m.clear();
    cin >> n;
    for (int i = 1; i <= n; i++) {
      int a, b;
      cin >> a >> b;
      if (m[a].first < b)
        m[a] = {b, i};
    }
    cout << m.size() << endl;
    for (auto op : m) {
      cout << op.second.second << ' ';
    }
    cout << endl;
  }
}