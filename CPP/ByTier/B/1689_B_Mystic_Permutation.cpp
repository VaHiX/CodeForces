/*
 * Problem URL : https://codeforces.com/problemset/problem/1689/B
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;

int main() {

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
      cin >> a[i];
    if (n == 1) {
      cout << -1 << endl;
      continue;
    }
    int b[n];
    copy_n(a, n, b);
    sort(b, b + n);
    for (int i = 0; i < n - 1; i++) {
      if (a[i] == b[i]) {
        swap(b[i], b[i + 1]);
      }
    }
    if (a[n - 1] == b[n - 1])
      swap(b[n - 1], b[n - 2]);
    for (int i = 0; i < n; i++)
      cout << b[i] << " ";
    cout << endl;
  }
}