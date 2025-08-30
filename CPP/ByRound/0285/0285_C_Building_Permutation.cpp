/*
 * Problem URL : https://codeforces.com/problemset/problem/285/C
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
long long n;
long long a[400000], c;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++)
    c += abs(i - a[i]);
  cout << c;
  return 0;
}