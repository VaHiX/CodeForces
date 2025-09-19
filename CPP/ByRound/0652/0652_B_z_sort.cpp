/*
 * Problem URL : https://codeforces.com/problemset/problem/652/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int n, a[1111];
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0)
      cout << a[i / 2] << ' ';
    else
      cout << a[n - i / 2 - 1] << ' ';
  }
  return 0;
}