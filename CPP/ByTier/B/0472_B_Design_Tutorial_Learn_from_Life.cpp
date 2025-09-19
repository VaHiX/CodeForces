/*
 * Problem URL : https://codeforces.com/problemset/problem/472/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k, a[2000], sum = 0;
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  for (int i = n - 1; i >= 0; i -= k)
    sum += 2 * (a[i] - 1);
  cout << sum;
}
