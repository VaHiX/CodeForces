/*
 * Problem URL : https://codeforces.com/problemset/problem/35/D
 * Submit Date : 2025-08-16
 */

#include "bits/stdc++.h"
using namespace std;
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n, m, sum = 0, c1 = 0;
  cin >> n >> m;
  int c[n + 1];
  for (int i = 0; i < n; i++) {
    cin >> c[i];
    c[i] *= (n - i);
  }
  sort(c, c + n);
  for (int i = 0; i < n; i++) {
    sum += c[i];
    if (sum <= m)
      c1++;
    else
      break;
  }
  cout << c1;
}