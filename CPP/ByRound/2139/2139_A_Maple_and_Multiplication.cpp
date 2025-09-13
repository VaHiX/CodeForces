/*
 * Problem URL : https://codeforces.com/contest/2139/problem/A
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int x, y;
    cin >> x >> y;
    if (x == y)
      cout << "0\n";
    else if (x % y == 0 || y % x == 0)
      cout << "1\n";
    else
      cout << "2\n";
  }
}