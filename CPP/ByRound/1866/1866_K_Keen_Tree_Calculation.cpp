/*
 * Problem URL : https://codeforces.com/contest/1866/problem/K
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
// #include <bits/extc++.h>
using namespace std;
// using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 1e5 + 5, INF = 0x3f3f3f3f, MOD = 998244353;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
// const double PI=acos(-1);

vector<pii> s[MAXN];
pii p[MAXN];
ll l[MAXN];
pair<ll, int> ma[MAXN], sma[MAXN];

ll ans[MAXN];
vector<pii> Q[MAXN];

ll tempans = 0;
void dfs(int nd, int par, int w) {
  p[nd] = {par, w};
  l[nd] = l[par] + w;
  for (auto [i, j] : s[nd]) {
    if (i == par)
      continue;
    dfs(i, nd, j);
    if (ma[i].first + j > ma[nd].first) {
      sma[nd] = ma[nd];
      ma[nd] = {ma[i].first + j, i};
    } else if (ma[i].first + j > sma[nd].first)
      sma[nd] = {ma[i].first + j, i};
  }
  tempans = max(tempans, ma[nd].first + sma[nd].first);
}

void insert(deque<pll> &d, ll k, ll b) {
  while (!d.empty() && d.back().second <= b)
    d.pop_back();
  while (d.size() > 1) {
    auto [k1, b1] = d.back();
    double x = 1.0 * (b1 - b) / (k - k1);
    auto [k2, b2] = d[d.size() - 2];
    double x2 = 1.0 * (b2 - b1) / (k1 - k2);
    if (x <= x2)
      d.pop_back();
    else
      break;
  }
  d.push_back({k, b});
}
deque<pll> d, d2;
vector<pll> tmp, tmp2;
multiset<ll> st;
void dfs2(int nd) {
  d.clear();
  tmp.clear();
  d2.clear();
  tmp2.clear();
  for (auto [i, j] : s[nd]) {
    if (i == p[nd].first)
      continue;
    tmp.push_back({j, ma[i].first});
  }
  sort(tmp.begin(), tmp.end());
  for (auto [k, b] : tmp) {
    while (!d.empty() && d.back().second <= b) {
      tmp2.push_back(d.back());
      d.pop_back();
    }
    while (d.size() > 1) {
      auto [k1, b1] = d.back();
      double x = 1.0 * (b1 - b) / (k - k1);
      auto [k2, b2] = d[d.size() - 2];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x <= x2) {
        tmp2.push_back(d.back());
        d.pop_back();
      } else
        break;
    }
    d.push_back({k, b});
  }
  sort(tmp2.begin(), tmp2.end());
  for (auto [k, b] : tmp2) {
    insert(d2, k, b);
  }
  sort(Q[nd].begin(), Q[nd].end());
  pll last = {0, 0};
  for (auto [x, ind] : Q[nd]) {
    ans[ind] = tempans;
    while (d.size() > 1) {
      auto [k1, b1] = d[0];
      auto [k2, b2] = d[1];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x >= x2) {
        last = d[0];
        d.pop_front();
      } else
        break;
    }
    while (d2.size() > 1) {
      auto [k1, b1] = d2[0];
      auto [k2, b2] = d2[1];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x >= x2)
        d2.pop_front();
      else
        break;
    }

    ll k = 0, b = 0;
    if (!d.empty()) {
      k = d.front().first;
      b = d.front().second;
    }
    ll Ma = k * x + b, sMa = last.first * x + last.second;
    if (d.size() > 1) {
      auto [k2, b2] = d[1];
      sMa = max(sMa, k2 * x + b2);
    }
    if (!d2.empty()) {
      auto [k2, b2] = d2[0];
      sMa = max(sMa, k2 * x + b2);
    }

    ans[ind] = max(ans[ind], Ma + sMa);
    if (nd != 1 && !st.empty())
      ans[ind] = max(ans[ind], *st.rbegin() + l[p[nd].first] + Ma +
                                   1ll * x * p[nd].second);
  }
  for (auto [i, j] : s[nd]) {
    if (i == p[nd].first)
      continue;
    if (i == ma[nd].second)
      st.insert(sma[nd].first - l[nd]);
    else
      st.insert(ma[nd].first - l[nd]);
    dfs2(i);
    if (i == ma[nd].second)
      st.erase(st.find(sma[nd].first - l[nd]));
    else
      st.erase(st.find(ma[nd].first - l[nd]));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // freopen("case.txt","r",stdin);
  // freopen("ans.txt","w",stdout);

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    s[u].push_back({v, w});
    s[v].push_back({u, w});
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int x, k;
    cin >> x >> k;
    Q[x].push_back({k, i});
  }
  dfs(1, 0, 0);
  dfs2(1);
  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }

  return 0;
}