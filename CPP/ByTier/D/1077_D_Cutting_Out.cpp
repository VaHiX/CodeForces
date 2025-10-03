/*
 * Problem URL : https://codeforces.com/contest/1077/problem/D
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<pair<int, int>> ans;
  int n, k, a[200020] = {0}, p[200020] = {0};
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    p[a[i]]++;
  }
  for (int i = 0; i < 200020; i++) {
    for (int j = 1; j <= p[i]; j++)
      ans.push_back({p[i] / j, i});
  }
  sort(ans.begin(), ans.end());
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < k; i++)
    cout << ans[i].second << " ";
  return 0;
}
