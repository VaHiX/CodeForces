/*
 * Problem URL : https://codeforces.com/problemset/problem/1505/C
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
using namespace std;

int main() {

  string s;
  cin >> s;

  if (s.size() <= 2 || ((s[0] + s[1]) % 26 == s[2] - 'A'))
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}