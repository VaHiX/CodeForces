/*
 * Problem URL : https://codeforces.com/problemset/problem/2130/D
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
      int cnt = 0;
      for (int j = i + 1; j < n; j++) {
        if (v[j] > v[i]) {
          cnt++;
        }
      }
      int cnt2 = (n - v[i]) - cnt;
      sum += min(cnt, cnt2);
    }
    cout << sum << endl;
  }
  return 0;
}