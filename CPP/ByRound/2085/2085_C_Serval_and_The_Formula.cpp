/*
 * Problem URL : https://codeforces.com/problemset/problem/2085/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    long long x, y;
    cin >> x >> y;
    if (x == y)
      cout << "-1\n";
    else
      cout << (1ll << 32) - max(x, y) << "\n";
  }
  return 0;
}