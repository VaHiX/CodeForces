/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, k;
  cin >> n >> k;
  long long ar[n], x, c = 0;
  for (auto i = 0; i < n; i++)
    cin >> ar[i];
  sort(ar, ar + n);
  x = ar[(k - 1) / n];
  k--;
  for (auto i = 0; i < n; i++) {
    if (ar[i] < x)
      k -= n;
    if (ar[i] == x)
      c++;
  }
  cout << x << " " << ar[k / c];
  return 0;
}