/*
 * Problem URL : https://codeforces.com/contest/2148/problem/B
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, x, y, a;
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n + m; i++)
      cin >> a;
    cout << n + m << '\n';
  }
}