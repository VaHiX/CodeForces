/*
 * Problem URL : https://codeforces.com/problemset/problem/822/B
 * Submit Date : 2025-08-15
 */

#include <iostream>
using namespace std;
int n, m, a = 2e9, ai, j, c, i;
string s, t;
int main() {
  cin >> m >> n >> s >> t;
  for (i = 0; i <= n - m; i++) {
    for (j = c = 0; j < m; j++)
      t[i + j] != s[j] ? c++ : 0;
    c < a ? a = c, ai = i : 0;
  }
  cout << a << " ";
  for (j = 0; j < m; j++)
    t[ai + j] != s[j] ? cout << j + 1 << " ", 0 : 0;
  return 0;
}