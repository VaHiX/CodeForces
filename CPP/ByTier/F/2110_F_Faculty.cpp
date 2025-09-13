/*
 * Problem URL : https://codeforces.com/problemset/problem/2110/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[1000100];
int find(int x, int y) { return x % y + y % x; }
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    int ansn = 0, maxn = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > maxn) {
        if (a[i] >= maxn * 2) {
          maxn = a[i];
          for (int j = 1; j <= i; j++)
            ansn = max(ansn, find(a[j], a[i]));
        } else {
          maxn = a[i];
          ansn = a[i];
        }
      } else {
        ansn = max(ansn, find(maxn, a[i]));
      }
      cout << ansn << " ";
    }
    cout << endl;
  }
  return 0;
}