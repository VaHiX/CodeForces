/*
 * Problem URL : https://codeforces.com/contest/1453/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t, n, m, a;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    set<int> z;
    for (int i = 0; i < n + m; ++i) {
      cin >> a;
      z.insert(a);
    }
    cout << n + m - z.size() << "\n";
  }
  return 0;
}
