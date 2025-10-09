/*
 * Problem URL : https://codeforces.com/contest/363/problem/C
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  string s, s1 = "";
  cin >> s;
  char a = 1, b = 2, c = 3;
  int l;
  l = s.length();
  for (int i = 0; i < l; i++) {
    if (!(a == b and c == s[i]) and !(b == c and c == s[i])) {
      s1 += s[i];
      a = b;
      b = c;
      c = s[i];
    }
  }
  cout << s1;
}
