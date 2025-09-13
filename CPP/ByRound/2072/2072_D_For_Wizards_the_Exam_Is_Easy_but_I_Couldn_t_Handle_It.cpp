/*
 * Problem URL : https://codeforces.com/problemset/problem/2072/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
      cin >> x;
    int best = 0, L = 1, R = 1;
    for (int i = 0; i < n; i++) {
      int d = 0;
      for (int j = i + 1; j < n; j++) {
        if (a[j] > a[i])
          d++;
        else if (a[j] < a[i])
          d--;
        if (d < best) {
          best = d;
          L = i + 1;
          R = j + 1;
        }
      }
    }
    cout << L << " " << R << "\n";
  }
  return 0;
}
