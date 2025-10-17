/*
 * Problem URL : https://codeforces.com/problemset/problem/1462/C
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, ans = 0, p = 1;
    cin >> n;
    for (int i = 9; i; i--)
      if (n >= i)
        n -= i, ans += p * i, p *= 10;
    if (n)
      cout << "-1" << '\n';
    else
      cout << ans << endl;
  }
  return 0;
}
