/*
 * Problem URL : https://codeforces.com/contest/406/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int const MOD = 1e9 + 7;
using i64 = long long;
const int N = 1005;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += a[i][i];
    ans = ans % 2;
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    if (x == 3) {
      cout << ans;
    } else {
      cin >> x;
      ans = !ans;
    }
  }
  return 0;
}