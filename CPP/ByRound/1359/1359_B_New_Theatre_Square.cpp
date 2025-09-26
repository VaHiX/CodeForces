/*
 * Problem URL : https://codeforces.com/problemset/problem/1359/B
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, m, x, y, a, k;
string s;
main() {
  for (cin >> t; t--;) {
    cin >> n >> m >> x >> y;
    k = 2 * x;
    a = 0;
    while (n--) {
      cin >> s;
      for (int i = 0; i < m; i++) {
        if (s[i] == '.' && s[i + 1] == '.' && k > y)
          a += y, i++;
        else {
          if (s[i] == '.')
            a += x;
        }
      }
    }
    cout << a << endl;
  }
}