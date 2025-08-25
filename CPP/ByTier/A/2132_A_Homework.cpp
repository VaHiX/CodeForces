/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int T;
int n, m;
string a, b, c;
int main() {
  cin >> T;
  while (T--) {
    cin >> n >> a;
    cin >> m >> b >> c;
    for (int i = 0; i < m; i++) {
      if (c[i] == 'V')
        a = b[i] + a;
      else
        a = a + b[i];
    }
    cout << a << endl;
  }
  return 0;
}