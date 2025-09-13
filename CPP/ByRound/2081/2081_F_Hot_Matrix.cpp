/*
 * Problem URL : https://codeforces.com/problemset/problem/2081/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    if (n % 2 == 0 || n == 1) {
      cout << "YES\n";
      vector<int> a(n), b(n);
      for (int i = 1; i < n; i++) {
        if (i & 1)
          a[i] = (i + 1) / 2;
        else
          a[i] = n - i / 2;
        b[a[i]] = i;
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cout << b[(a[i] + a[j]) % n] << " \n"[j + 1 == n];
        }
      }
    } else
      cout << "NO\n";
  }
}