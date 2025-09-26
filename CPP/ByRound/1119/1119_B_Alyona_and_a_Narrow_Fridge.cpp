/*
 * Problem URL : https://codeforces.com/contest/1119/problem/B
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
int i, n, k, r, j, a[300000];
int main() {
  for (cin >> n >> k; i < n; i++) {
    cin >> a[i];
    sort(a, a + i + 1);
    r = 0;
    j = i;
    while (j > -1) {
      r += a[j];
      j -= 2;
    }
    if (r > k) {
      cout << i;
      return 0;
    }
  }
  cout << i;
}