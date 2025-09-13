/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/A
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int x, y;
    int mx = 0, my = 0, a = 0, b = 0;
    for (int i = 0; i < n; i++) {
      cin >> x;
      cin >> y;
      mx = max(mx, x);
      my = max(my, y);
      a = min(x, a);
      b = min(y, b);
    }
    cout << 2 * (mx + my - a - b) << endl;
  }
}