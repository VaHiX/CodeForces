/*
 * Problem URL : https://codeforces.com/contest/1951/problem/I
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define ll long long
#define sz(a) ((int)(a).size())
#define vi vector<int>
#define me(a, x) memset(a, x, sizeof(a))
#define ull unsigned long long
#define ld __float128
#define pb emplace_back
#define int long long
using namespace std;
#define i128 __int128
const int N = 807;
template <int N, int Ne> struct flows {
  using F = ll; // flow type
  F inf = 1e18;
  int n, s, t; // Remember to assign n, s and t !
  int ehd[N], cur[N], ev[Ne << 1], enx[Ne << 1], eid = 1;
  void clear() {
    eid = 1;
    memset(ehd, 0, sizeof(ehd));
    me(cur, 0);
    me(ev, 0);
    me(enx, 0);
  }
  F ew[Ne << 1], dis[N];
  void Eadd(int u, int v, F w) {
    ++eid, enx[eid] = ehd[u], ew[eid] = w, ev[eid] = v, ehd[u] = eid;
  }
  void add(int u, int v, F w) { Eadd(u, v, w), Eadd(v, u, 0); }
  bool bfs() {
    queue<int> q;
    L(i, 1, n) dis[i] = inf, cur[i] = ehd[i];
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = ehd[u]; i; i = enx[i])
        if (ew[i] && dis[ev[i]] == inf) {
          dis[ev[i]] = dis[u] + 1, q.push(ev[i]);
        }
    }
    return dis[t] < inf;
  }
  F dfs(int x, F now) {
    if (!now || x == t)
      return now;
    F res = 0, f;
    for (int i = cur[x]; i; i = enx[i]) {
      cur[x] = i;
      if (ew[i] && dis[ev[i]] == dis[x] + 1) {
        f = dfs(ev[i], min(now, ew[i])), ew[i] -= f, now -= f, ew[i ^ 1] += f,
        res += f;
        if (!now)
          break;
      }
    }
    return res;
  }
  F max_flow() {
    F res = 0;
    while (bfs())
      res += dfs(s, inf);
    return res;
  }
};
flows<N, N> G;
int n, m;
ll k;
int eu[N], ev[N];
ll ea[N], eb[N];
ll use[N], cu[N];
ll EW[N];
bool CHECK() {
  G.clear();
  vector<ll> deg(n + 1), bot(n + 1);
  G.n = n;
  G.s = ++G.n;
  G.t = ++G.n;
  ll sume = 0;
  L(t, 1, m) {
    G.add(eu[t], ev[t], cu[t]);
    deg[eu[t]] += cu[t];
    sume += cu[t];
  }
  L(i, 1, n) {
    G.add(G.s, i, deg[i]);
    bot[i] = G.eid ^ 1;
    G.add(i, G.t, k);
  }
  if (G.max_flow() != sume)
    return 0;
  L(i, 1, G.eid) EW[i] = G.ew[i];
  L(i, 1, n) {
    L(i, 1, G.eid) G.ew[i] = EW[i];
    G.ew[bot[i]] += k;
    if (G.max_flow() != k) {
      return 0;
    }
  }
  return 1;
}
int ban[N];
void Main() {
  cin >> n >> m >> k;
  L(i, 1, m) {
    cin >> eu[i] >> ev[i] >> ea[i] >> eb[i];
    use[i] = cu[i] = 0;
    ban[i] = 0;
  }
  ll mxt = 3e13, cur = 0;
  while (true) {
    int all_ban = 1;
    L(i, 1, m)
    if (!ban[i])
      all_ban = 0;
    if (all_ban)
      break;
    ll l = cur, r = mxt, ans = cur - 1;
    while (l <= r) {
      ll mid = (l + r) >> 1;
      L(i, 1, m) {
        cu[i] = use[i];
        if (!ban[i]) {
          cu[i] = max((mid + ea[i] - eb[i]) / (2 * ea[i]), 0LL);
        }
      }
      if (CHECK()) {
        L(i, 1, m) if (!ban[i]) use[i] = cu[i];
        ans = mid, l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    // if(ans==cur-1)assert(false);
    L(i, 1, m) { cu[i] = use[i]; }
    // ea (2cu+1) + eb
    L(i, 1, m) if (!ban[i] && ea[i] * (2 * cu[i] + 1) + eb[i] == ans + 1) {
      ++cu[i];
      if (CHECK()) {
        ++use[i];
      } else {
        ban[i] = 1;
        --cu[i];
      }
    }
    cur = ans + 1;
  }
  ll cnte = 0;
  ll ans = 0;
  L(i, 1, m) {
    ans += use[i] * use[i] * ea[i] + eb[i] * use[i];
    cnte += use[i];
  }
  assert(cnte == (n - 1) * k);
  cout << ans << '\n';
}
signed main() {
  ios ::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    Main();
  return 0;
}
/*
dp[n] = dp[0] = 0
dp[i] = (n-i+1)/n + (dp[i + 1] + dp[i - 1]) / 2
dp[i] - dp[i-1] = dp[i+1]-dp[i] + (m-i+1)/m
*/