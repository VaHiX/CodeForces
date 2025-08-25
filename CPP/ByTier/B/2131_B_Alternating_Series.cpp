/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/B
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;

int t, n;

int main() {
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cout << (i % 2 ? -1 : 3 - (i == n)) << ' ';
    }
    cout << '\n';
  }
  return 0;
}