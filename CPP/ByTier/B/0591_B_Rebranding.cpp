/*
 * Problem URL : https://codeforces.com/contest/591/problem/B
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;

main() {
  ios::sync_with_stdio(0);
  int l, o;
  cin >> l >> o;
  string s;
  cin >> s;
  char a[26], b[26];
  for (int i = 0; i < 26; i++)
    a[i] = 'a' + i;
  for (int i = 0; i < o; i++) {
    char c1, c2;
    cin >> c1 >> c2;
    swap(a[c1 - 'a'], a[c2 - 'a']);
  }
  for (int i = 0; i < 26; i++)
    b[a[i] - 'a'] = i + 'a';
  for (int i = 0; i < l; i++)
    cout << b[s[i] - 'a'];
}