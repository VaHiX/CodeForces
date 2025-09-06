/*
 * Problem URL : https://codeforces.com/contest/2039/problem/G
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

const int N = 1e6 + 9, T = 1e7 + 9, RT = 33333, mod = 998244353; 
using ll = long long;

int power(int n, long long k) {
  int ans = 1 % mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}

int SQRT(int n) {
  int x = sqrt(n);
  while (x * x < n) ++x;
  while (x * x > n) --x;
  return x;
}

int spf[T], id[T], DIAMETER, mu[T];
vector<int> primes; // 1 indexed
int prefix_prime_count[T], prefix_sum_mu[T];
void init() {
  mu[1] = 1;
  for(int i = 2; i < T; i++) {
    if (spf[i] == 0) spf[i] = i, mu[i] = i <= DIAMETER ? 0 : -1, primes.push_back(i);
    int sz = primes.size();
    for (int j = 0; j < sz && i * primes[j] < T && primes[j] <= spf[i]; j++) {
      spf[i * primes[j]] = primes[j];
      if (i % primes[j] == 0) mu[i * primes[j]] = 0;
      else mu[i * primes[j]] = mu[i] * (primes[j] <= DIAMETER ? 0 : -1);
    }
  }
  primes.insert(primes.begin(), 0);
  for (int i = 1; i < primes.size(); i++) {
    id[primes[i]] = i;
  }
  for (int i = 2; i < T; i++) {
    prefix_prime_count[i] = prefix_prime_count[i - 1] + (spf[i] == i);
  }
  for (int i = 1; i < T; i++) prefix_sum_mu[i] = prefix_sum_mu[i - 1] + mu[i];
}
int cnt[N]; // count of nodes having each diameter
int m;
namespace GoodNumbers { // numbers which aren't divisible by the first k primes
  gp_hash_table<int, int, custom_hash> mp[RT << 1];
  int count_num(int n, int k) { // n is a floor value, returns good numbers <= n
    if (k == 0 or n == 0) return n;
    if (primes[k] >= n) return 1;
    if (n < T and 1LL * primes[k] * primes[k] > n) {
      return 1 + prefix_prime_count[n] - k;
    }
    if (mp[k].find(n) != mp[k].end()) return mp[k][n];
    int ans;
    if (1LL * primes[k] * primes[k] > n) {
      int x = upper_bound(primes.begin(), primes.begin() + k, (int)SQRT(n)) - primes.begin() - 1;
      ans = count_num(n, x) - (k - x);
    }
    else ans = count_num(n, k - 1) - count_num(n / primes[k], k - 1);
    mp[k][n] = ans;
    return ans;
  }
};

vector<pair<int, int>> v;
namespace Dirichlet {
  // good number = numbers that aren't divisible by any prime <= DIAMETER
  // we will run dirichlet imagining there exists no prime <= DIAMETER
  gp_hash_table<int, int, custom_hash> mp;
  int p_c(int n) {
    return n < 1 ? 0 : 1;
  }
  int p_g(int n) {
    return GoodNumbers::count_num(n, v.back().first);
  }
  int solve (int x) { // sum of mob[i] over 1 <= i <= x and i is a good number
    if (x < T) return prefix_sum_mu[x];
    if (mp.find(x) != mp.end()) return mp[x];
    int ans = 0;
    for (int i = 2, last; i <= x; i = last + 1) {
      last = x / (x / i);
      ans += solve(x / i) * (p_g(last) - p_g(i - 1));
    }
    ans = p_c(x) - ans;
    return mp[x] = ans;
  }
};

int count_primes(int n) {
  if (n < T) return prefix_prime_count[n];
  int x = SQRT(n);
  int k = upper_bound(primes.begin(), primes.end(), x) - primes.begin() - 1;
  return GoodNumbers::count_num(n, k) + k - 1;
}


// diameter > 2 * sqrt(m)
void solve_large() {
  // only primes are good, so count total ways
  // and subtract where gcd is prime (means all nodes have a fixed prime)
  int total_ways = 1;
  int primes_under_m = count_primes(m);
  for (auto [k, c]: v) {
    if (m <= primes[k]) break;
    total_ways = 1LL * total_ways * power((primes_under_m - k + 1) % mod, c) % mod; // 1 or a prime > k
  }
  int bad_ways = (max(0, primes_under_m - v.back().first)) % mod;
  int ans = (total_ways - bad_ways + mod) % mod;
  cout << ans << '\n';
}

// diameter <= 2 * sqrt(m)
void solve_small() {
  int ans = 0;
  for (int l = 1, r; l <= m; l = r + 1) {
    int x = m / l;
    r = m / x;
    int cur = ((Dirichlet::solve(r) - Dirichlet::solve(l - 1)) % mod + mod) % mod;
    if (cur) {
      int mul = 1;
      for (auto [k, c]: v) {
        if (x <= primes[k]) break;
        mul = 1LL * mul * power(GoodNumbers::count_num(x, k) % mod, c) % mod;
      }
      ans += 1LL * cur * mul % mod;
      ans %= mod;
    }
  }
  cout << ans << '\n';
}

vector<int> g[N];
int dp[N], up[N];
void dfs(int u, int p = 0) {
  dp[u] = 0;
  if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
  for (auto v: g[u]) {
    if (v ^ p) {
      dfs(v, u);
      dp[u] = max(dp[u], dp[v] + 1);
    }
  }
}
int pref[N], suf[N];
void dfs2(int u) {
  int sz = g[u].size();
  for (int i = 0; i < sz; i++) {
    int v = g[u][i];
    pref[i] = dp[v] + 1;
    if (i) pref[i] = max(pref[i], pref[i - 1]);
  }
  for (int i = sz - 1; i >= 0; i--) {
    int v = g[u][i];
    suf[i] = dp[v] + 1;
    if (i + 1 < sz) suf[i] = max(suf[i], suf[i + 1]);
  }
  for (int i = 0; i < sz; i++) {
    int v = g[u][i];
    int cur = up[u];
    if (i) cur = max(cur, pref[i - 1]);
    if (i + 1 < sz) cur = max(cur, suf[i + 1]);
    up[v] = cur + 1;
  }
  for (auto v: g[u]) {
    dfs2(v);
  }
}
int mx_d[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n >> m;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  dfs2(1);
  for (int u = 1; u <= n; u++) {
    vector<int> vec;
    if (u != 1) vec.push_back(up[u]);
    for (auto v: g[u]) {
      vec.push_back(dp[v] + 1);
    }
    sort(vec.rbegin(), vec.rend());
    mx_d[u] = vec[0];
    if (vec.size() > 1) {
      mx_d[u] += vec[1];
    }
    mx_d[u] += 1;
  }
  for (int i = 1; i <= n; i++) {
    cnt[mx_d[i]]++;
    DIAMETER = max(DIAMETER, mx_d[i]);
  }

  init();

  int last_prime = 0;
  for (int i = 2; i <= DIAMETER; i++) {
    if (spf[i] == i) last_prime = i;
    if (cnt[i]) {
      int k = id[last_prime];
      if (!v.empty() and v.back().first == k) {
        v.back().second += cnt[i];
      } else {
        v.push_back({k, cnt[i]});
      }
    }
  }

  if (DIAMETER > 2 * SQRT(m)) solve_large();
  else solve_small();
  return 0;
}