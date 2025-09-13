/*
 * Problem URL : https://codeforces.com/contest/2138/problem/A
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int k, x;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> k >> x;
    int pos = 1;
    for (int i = 1; i <= k + 1; i++)
      if ((x >> i - 1) & 1) {
        pos = i;
        break;
      }
    pos++;
    cout << k + 1 - pos + 1 << '\n';
    for (int i = pos; i <= k + 1; i++) {
      if ((x >> i - 1) & 1)
        cout << 2 << " ";
      else
        cout << 1 << " ";
    }
    cout << '\n';
  }
  return 0;
}