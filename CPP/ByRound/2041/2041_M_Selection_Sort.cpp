/*
 * Problem URL : https://codeforces.com/contest/2041/problem/M
 * Submit Date : 2025-08-25
 */

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> vp(n);
  for (int i = 0; i < n; i++) {
    cin >> vp[i].first;
    vp[i].second = i;
  }
  sort(vp.begin(), vp.end());
  int idx[n];
  for (int i = 0; i < n; i++) {
    idx[vp[i].second] = i;
  }
  long long ans = 1e18;
  int al_sort_idx = 0;
  int in_s[n] = {0};
  for (int i = 0; i < n; i++) {
    in_s[idx[i]] = 1;
    while (al_sort_idx < n &&
           (in_s[al_sort_idx] || idx[al_sort_idx] == al_sort_idx)) {
      al_sort_idx++;
    }
    ans = min(ans, 1LL * (i + 1) * (i + 1) +
                       1LL * (n - al_sort_idx) * (n - al_sort_idx));
  }
  memset(in_s, 0, sizeof(in_s));
  al_sort_idx = n - 1;
  for (int i = n - 1; i >= 0; i--) {
    in_s[idx[i]] = 1;
    while (al_sort_idx >= 0 &&
           (in_s[al_sort_idx] || idx[al_sort_idx] == al_sort_idx)) {
      al_sort_idx--;
    }
    ans = min(ans, 1LL * (n - i) * (n - i) +
                       1LL * (al_sort_idx + 1) * (al_sort_idx + 1));
  }

  cout << ans << '\n';
  return 0;
}
