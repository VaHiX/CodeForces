/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int t, f, n;
string a, b;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> a >> b;
    f = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == '#' && b[i] == '#')
        continue;
      if (a[i] == '.' && b[i] == '#') {
        if (i == n - 1 || a[i + 1] == '#') {
          cout << "None\n";
          f = 1;
          break;
        }
        a[i] = a[i + 1] = '#';
        // 找o格
      } else if (b[i] == '.' && a[i] == '#') {
        if (i == n - 1 || b[i + 1] == '#') {
          cout << "None\n";
          f = 1;
          break;
        }
        b[i] = b[i + 1] = '#';

      } else {
        if (i < n - 1 && a[i + 1] == '.' && b[i + 1] == '.')
          f = 2;
        a[i] = b[i] = '#';
      }
    }
    if (f == 0)
      cout << "Unique\n";
    else if (f == 2)
      cout << "Multiple\n";
  }
  return 0;
}