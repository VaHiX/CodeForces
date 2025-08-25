/*
 * Problem URL : https://codeforces.com/problemset/problem/2130/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, s = 0;
    cin >> n;
    while (n--) {
      int x;
      cin >> x;
      s += (x ? x : 1);
    }
    cout << s << "\n";
  }
  return 0;
}