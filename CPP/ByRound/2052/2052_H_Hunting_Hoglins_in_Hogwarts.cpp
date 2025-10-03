/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve(ll n) {
  vector<pair<ll, ll>> ran = {{1, n}};
  while (true) {
    vector<pair<ll, ll>> nxt;
    bool ok = 0;
    for (auto [l, r] : ran) {
      if (l > r)
        continue;
      ll m = (l + r) >> 1;
      nxt.emplace_back(l, m - 1);
      nxt.emplace_back(m + 1, r);
      cout << m << endl;
      int cu;
      cin >> cu;
      if (cu >= 2)
        return;
      if (cu == 1) {
        ok = 1;
        break;
      }
    }
    while (!ok) {
      cout << 0 << endl;
      int cu;
      cin >> cu;
      ok = cu;
    }
    reverse(nxt.begin(), nxt.end());
    ran = nxt;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, t;
  cin >> n >> t;
  while (t--)
    solve(n);
}
