/*
 * Problem URL : https://codeforces.com/problemset/problem/2102/E
 * Submit Date : 2025-08-18
 */

#include "bits/stdc++.h"
#define FAST                                                                   \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;

int main() {
  FAST;
  int Tt;
  cin >> Tt;
  while (Tt--) {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> v[i];

    vector<int> pref(n + 1);
    vector<int> suf(n + 1);

    set<int> s;
    for (int i = 1; i <= n; i++)
      s.insert(i);

    for (int i = 1; i <= n; i++) {
      auto it = s.upper_bound(v[i]);
      if (it != s.begin())
        s.erase(prev(it));

      pref[i] = n - s.size();
    }

    for (int i = 1; i <= n; i++)
      s.insert(i);

    for (int i = n; i >= 1; i--) {
      auto it = s.upper_bound(v[i]);
      if (it != s.begin())
        s.erase(prev(it));

      suf[i] = n - s.size();
    }

    long long ans = 0;

    for (int i = 1; i < n; i++)
      ans += min(pref[i], suf[i + 1]);
    cout << ans << "\n";
  }
  return 0;
}