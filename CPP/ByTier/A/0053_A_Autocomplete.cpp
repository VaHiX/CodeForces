/*
 * Problem URL : https://codeforces.com/problemset/problem/53/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  string a, b, c = "z";
  int n, i;
  cin >> a >> n;
  for (i = 0; i < n; i++) {
    cin >> b;
    if (b.substr(0, a.size()) == a && (b < c))
      c = b;
  }
  if (c == "z")
    cout << a << endl;
  else
    cout << c << endl;
}