/*
 * Problem URL : https://codeforces.com/problemset/problem/987/C
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> s(n), c(n);
  for (int &i : s)
    cin >> i;
  for (int &i : c)
    cin >> i;

  int res = 1e9;
  for (int i = 0; i < n; i++) {
    int l = 1e9;
    for (int j = 0; j < i; j++)
      if (s[j] < s[i])
        l = min(l, c[j]);
    int r = 1e9;
    for (int j = i + 1; j < n; j++)
      if (s[i] < s[j])
        r = min(r, c[j]);
    res = min(res, l + c[i] + r);
  }
  if (res == 1e9)
    res = -1;
  cout << res << endl;
  return 0;
}
