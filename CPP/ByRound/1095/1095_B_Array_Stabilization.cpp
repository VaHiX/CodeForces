/*
 * Problem URL : https://codeforces.com/contest/1095/problem/B
 * Submit Date : 2025-08-29
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, n;
  cin >> n;
  int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  cout << min(a[n - 1] - a[1], a[n - 2] - a[0]);
}