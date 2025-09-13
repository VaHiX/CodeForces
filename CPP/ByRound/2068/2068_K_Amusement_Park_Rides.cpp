/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/K
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int cap[2020], rev[2020];
vector<int> match[2020];
bool vis[2020];
vector<int> e[4040];
map<int, int> cnt;
priority_queue<pll> pq;
vector<int> cand;

bool dfs(int now) {
  for (auto nxt : e[now]) {
    if (vis[nxt])
      continue;
    vis[nxt] = 1;
    if (cap[nxt] > match[nxt].size()) {
      match[nxt].push_back(now);
      return 1;
    } else
      for (int i = 0; i < match[nxt].size(); i++)
        if (dfs(match[nxt][i])) {
          match[nxt][i] = now;
          return 1;
        }
  }
  return 0;
}

void init(int n) {
  for (int i = 1; i <= n; i++) {
    cap[i] = rev[i] = 0;
    match[i].clear();
  }
  for (int i = 1; i <= 2 * n; i++)
    e[i].clear();
  cnt.clear();
  while (pq.size())
    pq.pop();
  cand.clear();
}

void solve() {
  int n;
  cin >> n;
  int IDX = 0;
  init(n);
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    cnt[a]++;
  }
  for (auto &[key, val] : cnt) {
    cap[++IDX] = val;
    rev[IDX] = key;
    pq.push({-key, IDX});
  }
  ll ans = 0;
  int iidx = 0;
  while (pq.size()) {
    ll tmp = pq.top().first;
    iidx++;
    while (pq.size() && pq.top().first == tmp) {
      cand.push_back(pq.top().second);
      pq.pop();
      e[iidx].push_back(cand.back());
    }
    memset(vis, 0, sizeof(vis));
    if (dfs(iidx)) {
      ans = tmp;
      for (auto i : cand)
        pq.push({tmp - rev[i], i});
    }
    cand.clear();
  }
  cout << -ans << '\n';
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    solve();
}