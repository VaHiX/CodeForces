/*
 * Problem URL : https://codeforces.com/contest/2034/problem/D
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a)
    cin >> i;
  int j = n - 1, k = n - 1, ans = 0;
  vector<pair<int, int>> move;
  for (int i = 0; i < n; i++) {
    j = max(j, k);
    if (a[i] == 2) {
      while (i < j && a[j] != 1)
        j--; // 1
      if (i < j && a[j] == 1) {
        move.push_back({i, j});
        ans++;
        swap(a[i], a[j]);
      }
    }
    if (a[i] == 1) {
      while (i < k && a[k] != 0)
        k--; // 0
      if (i < k && a[k] == 0) {
        move.push_back({i, k});
        ans++;
        swap(a[i], a[k]);
      }
    }
  }
  cout << ans << "\n";
  for (auto [a, b] : move)
    cout << a + 1 << " " << b + 1 << "\n";
  // for(auto i:a) cout<<i<<" ";
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
