/*
 * Problem URL : https://codeforces.com/problemset/problem/246/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int arr[120], n, k;
int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  sort(arr, arr + n);
  int t = 0, g = 0;
  for (int i = 0; i < k; i++) {
    cout << t + 1 << ' ';
    for (int j = 0; j < t; j++)
      cout << arr[n - j - 1] << ' ';
    cout << arr[g] << '\n';
    g++;
    if (g == n - t) {
      t++;
      g = 0;
    }
  }
}
