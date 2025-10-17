/*
 * Problem URL : https://codeforces.com/problemset/problem/1009/B
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  string s;
  cin >> s;
  string f;
  int c = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '1')
      c++;
    else
      f += s[i];
  }
  int k = 0;
  while (k < f.size() && f[k] == '0')
    k++;

  f.insert(k, string(c, '1'));
  cout << f;
  return 0;
}
