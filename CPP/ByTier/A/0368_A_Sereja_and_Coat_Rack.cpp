/*
 * Problem URL : https://codeforces.com/contest/368/problem/A
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, j, k;
  int n, d, m;
  int sum = 0;

  cin >> n >> d;
  int a[n];

  for (i = 0; i < n; i++)
    cin >> a[i];

  cin >> m;

  if (m > n) {
    for (i = 0; i < n; i++) {
      sum += a[i];
    }

    sum -= (m - n) * d;
  }

  else {
    sort(a, a + n);
    for (i = 0; i < m; i++) {
      sum += a[i];
    }
  }

  cout << sum;

  return 0;
}
