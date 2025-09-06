/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const ll inf = 2e18;
const ll mod = 998244353;

void run_case() {
  ll n, m;
  cin >> n >> m;
  vector<array<ll, 3>> a(n);
  vector<ll> t;
  for (ll i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1] >> a[i][2];
    t.push_back(a[i][2]);
  }
  sort(t.begin(), t.end());
  t.erase(unique(t.begin(), t.end()), t.end());
  vector<ll> unused;
  if (t[0] != 0) {
    unused.push_back(0);
    if (t[0] != 1) {
      unused.push_back(1);
    }
  }
  if (t.back() != 1e9) {
    unused.push_back(1e9);
    if (t.back() != 1e9 - 1) {
      unused.push_back(1e9 - 1);
    }
  }
  for (ll i = 1; i < t.size(); i++) {
    if (t[i] != t[i - 1] + 1) {
      unused.push_back(t[i] - 1);
      if (t[i] != t[i - 1] + 2) {
        unused.push_back(t[i] - 2);
      }
      break;
    }
  }
  for (ll i = 0; i < n; i++) {
    a[i][2] = lower_bound(t.begin(), t.end(), a[i][2]) - t.begin();
  }
  ll Asz;
  cin >> Asz;
  vector<ll> A(Asz), Amn(t.size(), inf);
  vector<vector<ll>> Bs(t.size());
  for (ll i = 0; i < Asz; i++) {
    cin >> A[i];
    A[i]--;
  }
  ll Bsz;
  cin >> Bsz;
  vector<ll> B(Bsz);
  ll mx = 0;
  for (ll i = 0; i < Bsz; i++) {
    cin >> B[i];
    B[i]--;
    mx = max(mx, a[B[i]][0]);
    Bs[a[B[i]][2]].push_back(B[i]);
  }
  ll mn1 = inf, mn2 = inf;
  for (ll i = 0; i < Asz; i++) {
    if (a[A[i]][1] <= mx) {
      cout << "-1\n";
      return;
    }
    if (a[A[i]][0] <= mx) {
      Amn[a[A[i]][2]] = min(Amn[a[A[i]][2]], a[A[i]][1]);
      mn1 = min(mn1, a[A[i]][0]);
    } else {
      mn2 = min(mn2, a[A[i]][0]);
    }
  }
  vector<ll> sc(n, 0);
  vector<pll> ans;
  if (mn1 != inf) {
    ans.push_back({mn1, unused[0]});
    for (ll i = 0; i < n; i++) {
      if (a[i][0] >= mn1) {
        sc[i]++;
      }
    }
  }
  if (mn2 != inf) {
    ans.push_back({mn2, unused[1]});
  }
  for (ll i = 0; i < t.size(); i++) {
    if (Amn[i] == inf)
      continue;
    ans.push_back({Amn[i], t[i]});
    for (auto &j : Bs[i]) {
      if (a[j][1] >= Amn[i]) {
        sc[j]++;
      }
    }
  }
  for (ll i = 0; i < n; i++) {
    if (sc[i] >= 2) {
      cout << "-1\n";
      return;
    }
  }
  cout << ans.size() << '\n';
  for (auto &[x, y] : ans) {
    cout << x << ' ' << y << '\n';
  }
}

int main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  int tc;
  cin >> tc;
  while (tc--) {
    run_case();
  }
}
