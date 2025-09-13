/*
 * Problem URL : https://codeforces.com/problemset/problem/208/D
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>
using namespace std;
long long n, p[51], a[6], b[6], m;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i];
  for (int i = 1; i < 6; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++) {
    m += p[i];
    for (int i = 5; i > 0; i--)
      b[i] += m / a[i], m -= m / a[i] * a[i];
  }
  for (int i = 1; i < 6; i++)
    cout << b[i] << " ";
  cout << "\n" << m;
  return 0;
}
