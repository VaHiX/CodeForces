/*
 * Problem URL : https://codeforces.com/problemset/problem/2065/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    if (abs(n - m) > k || max(m, n) < k)
      cout << "-1" << endl;
    else {
      int t = max(m, n) - k;
      for (int i = 0; i < n - t; i++)
        cout << "0";
      for (int i = 0; i < t; i++)
        cout << "10";
      for (int i = 0; i < m - t; i++)
        cout << "1";
      cout << endl;
    }
  }
}