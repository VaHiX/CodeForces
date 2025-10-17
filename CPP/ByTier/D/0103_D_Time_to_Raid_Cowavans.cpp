/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <array>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define endl '\n'
#define lowbit(x) ((x) & (-(x)))
#define all(x) begin(x), end(x)
#define all2(x) begin(x) + 1, end(x)
const int N = 2e5 + 10;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ll INF = 0x3f3f3f3f;
const ll INF2 = 0x3f3f3f3f3f3f3f3f;

void Satori() {
  int n;
  cin >> n;
  vector<ll> w(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> w[i];
  int q;
  cin >> q;
  vector<vector<array<int, 2>>> qur(n + 1);
  for (int i = 1; i <= q; ++i) {
    int a, b;
    cin >> a >> b;
    qur[b].push_back({a, i});
  }
  vector<ll> ans(q + 1);
  int sq = sqrt(n);
  for (int i = 1; i <= n; ++i) {
    if (qur[i].size() == 0)
      continue;
    if (i <= sq) {
      vector<ll> suf(n + 2);
      for (int j = n; j >= 1; j--)
        suf[j] = suf[min(j + i, n + 1)] + w[j];
      for (auto [a, id] : qur[i])
        ans[id] = suf[a];
    } else {
      for (auto [a, id] : qur[i]) {
        ll res = 0;
        for (int j = a; j <= n; j += i)
          res += w[j];
        ans[id] = res;
      }
    }
  }
  for (int i = 1; i <= q; ++i)
    cout << ans[i] << endl;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;

  for (int i = 1; i <= t; i++)
    Satori();
  return 0;
}