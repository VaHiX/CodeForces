/*
 * Problem URL : https://codeforces.com/problemset/problem/1846/B
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>
using namespace std;
char c[10];
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    string s = "DRAW";
    for (int i = 1; i <= 9; ++i)
      cin >> c[i];
    for (int i = 1; i <= 9; ++i)
      for (int j = i + 1; j <= 9; ++j)
        for (int k = j + 1; k <= 9; ++k) {
          if (c[i] != '.' && c[i] == c[j] && c[j] == c[k] && j - i == k - j &&
              (j - i != 2 || i == 3) &&
              (j - i != 1 || i == 1 || i == 4 || i == 7))
            s = c[i];
        }
    cout << s << '\n';
  }
  return 0;
}