/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
  int n, k, p;
  cin >> n >> k >> p;
  if (k == 0) {
    while (p--) {
      int a;
      cin >> a;
      cout << ".";
    }
    cout << endl;
    return;
  }
  if (n % 2 == 1) {
    n--;
    k--;
  }
  while (p--) {
    int a;
    cin >> a;
    if (a == n + 1) {
      cout << "X";
    } else {
      if (a % 2 == 0 && k * 2 >= n - a + 2) {
        cout << "X";
      } else if (a % 2 == 0) {
        cout << ".";
      } else if (a % 2 == 1 && k >= n - a / 2) {
        cout << "X";
      } else
        cout << ".";
    }
  }
  cout << endl;
}
signed main() {
  int t = 1;
  while (t--)
    solve();
  return 0;
}