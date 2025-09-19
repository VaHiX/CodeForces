/*
 * Problem URL : https://codeforces.com/contest/586/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int k[101];
int main() {
  int n, i, z = 0;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> k[i];
    if (k[i] == 1)
      z++;
  }
  for (i = 2; i < n; i++)
    if (k[i] == 0 && k[i - 1] == 1 && k[i + 1] == 1)
      z++;
  cout << z;
}