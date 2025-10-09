/*
 * Problem URL : https://codeforces.com/contest/2003/problem/E1
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>
using namespace std;

main() {
  int t;
  cin >> t;
  while (t--) {
    int m, n;
    cin >> n >> m;
    pair<int, int> pr[m];
    for (int i = 0; i < m; i++) {
      cin >> pr[i].first >> pr[i].second;
    }
    long long int sum = 1LL * n * (n - 1) / 2;
    for (int i = 0, j = m - 1; i <= j; i++, j--) {
      sum = sum - (pr[j].second - pr[i].first);
    }

    cout << sum << endl;
  }

  return 0;
}