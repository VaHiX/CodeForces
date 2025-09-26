/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/B
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500103;

void solve() {
  int n, k;
  cin >> n >> k;
  int res = 0, o = 1;
  map<int, int> ans, occ;
  for (int i = 1, x; i <= n; i++)
    cin >> x, ans[x]++;
  for (auto [x, y] : ans)
    occ[y]++;
  for (auto [z, c] : occ) {
    while (k >= z && c)
      k -= z, c--;
    res += c;
  }
  res = max(res, 1);
  cout << res << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    solve();
}