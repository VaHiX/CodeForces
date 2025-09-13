/*
 * Problem URL : https://codeforces.com/contest/2136/problem/A
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int t, a, b, c, d;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c >> d;
    if (max(a, b) > min(a, b) * 2 + 2 ||
        max(c - a, d - b) > min(c - a, d - b) * 2 + 2)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}