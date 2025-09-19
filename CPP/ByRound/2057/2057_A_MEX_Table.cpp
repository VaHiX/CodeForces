/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    cout << max(a, b) + 1 << '\n';
  }
}