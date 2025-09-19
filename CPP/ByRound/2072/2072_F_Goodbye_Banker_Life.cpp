/*
 * Problem URL : https://codeforces.com/problemset/problem/2072/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int T, n, k, i;
  for (cin >> T; T > 0; T--) {
    cin >> n >> k;
    n--;
    for (i = 0; i <= n; i++) {
      if ((n & i) == i)
        cout << k << ' ';
      else
        cout << "0 ";
    }
    cout << '\n';
  }
  return 0;
}