/*
 * Problem URL : https://codeforces.com/contest/1531/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, fl = 0;
  string s = "blue";
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string st;
    cin >> st;
    if (st == "lock")
      fl = 1;
    else if (st == "unlock")
      fl = 0;
    else if (fl == 0)
      s = st;
  }
  cout << s;
}