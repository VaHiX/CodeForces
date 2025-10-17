/*
 * Problem URL : https://codeforces.com/problemset/problem/1201/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, k, i, sum;
  cin >> n >> k;
  long long a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  sum = a[n / 2];
  i = 1;
  while (i <= n / 2) {
    if (k < (a[n / 2 + i] * i - sum))
      break;
    sum += a[n / 2 + i];
    i++;
  }
  cout << (k + sum) / i;
  return 0;
}