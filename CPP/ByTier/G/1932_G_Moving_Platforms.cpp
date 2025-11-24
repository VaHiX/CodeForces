// Problem: CF 1932 G - Moving Platforms
// https://codeforces.com/contest/1932/problem/G

// # Moving Platforms Problem
// ## Algorithm: Dijkstra's with Modular Arithmetic
// ## Time Complexity: O((V + E) * log V * log H)
// ## Space Complexity: O(V + E)

#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
ll max(ll a, ll b) { return (a > b) ? a : b; }
ll min(ll a, ll b) { return (a < b) ? a : b; }
ll LASTBIT(ll mask) { return (mask) & (-mask); }
int pop_cnt(ll mask) { return __builtin_popcountll(mask); }
int ctz(ll mask) { return __builtin_ctzll(mask); }
int logOf(ll mask) { return __lg(mask); }
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <class T1, class T2> bool minimize(T1 &a, T2 b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T>
void printArr(T &container, char separator = ' ', char finish = '\n') {
  for (auto item : container)
    cout << item << separator;
  cout << finish;
}
template <class T> void remove_dup(vector<T> &a) {
  sort(ALL(a));
  a.resize(unique(ALL(a)) - a.begin());
}
ll gcd(ll a, ll b, ll &x, ll &y) {
  x = 1, y = 0;
  ll x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    ll q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}
const ll N = 1e5 + 69;
const ll INF = 1e18 + 69;
ll n, m, h;
ll l[N], s[N];
vector<ll> graph[N];
ll dis[N];
bool visited[N];
void reset() {
  for (ll i = 1; i <= n; ++i) {
    graph[i].clear();
    dis[i] = INF;
    visited[i] = false;
  }
}
struct P {
  ll i;
  ll w;
  P() {}
  P(ll _i, ll _w) { i = _i, w = _w; }
  bool operator<(P x) const { return w > x.w; }
};
ll normie(ll x) {
  x %= h;
  if (x < 0)
    x += h;
  return x;
}
ll solve() {
  cin >> n >> m >> h;
  for (ll i = 1; i <= n; ++i)
    cin >> l[i];
  for (ll i = 1; i <= n; ++i)
    cin >> s[i];
  reset();
  for (ll i = 0; i < m; ++i) {
    ll u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dis[1] = 0;
  priority_queue<P, vector<P>> pq;
  pq.push(P(1, 0));
  while (pq.size()) {
    P u = pq.top();
    pq.pop();
    if (visited[u.i])
      continue;
    visited[u.i] = 1;
    for (ll v : graph[u.i])
      if (dis[v] > dis[u.i]) {
        ll lmao = (dis[u.i]) % h; // Current time step
        ll d_slope = normie(s[u.i] - s[v]); // Difference in slope (how levels change)
        ll d_time = normie(l[v] + lmao * s[v] - (l[u.i] + lmao * s[u.i])); // When platforms align
        if (d_time == 0) {
          // Platforms are already aligned, move with 1 step
          if (minimize(dis[v], dis[u.i] + 1))
            pq.push(P(v, dis[v]));
          continue;
        }
        if (d_slope == 0)
          continue; // No change in level difference - can't align platforms with fixed slope
        ll g = __gcd(d_slope, (ll)h); // Find GCD to simplify equation
        if (d_time % g)
          continue; // Not divisible by GCD, so no solution exists
        d_slope /= g;
        d_time /= g;
        h /= g;
        ll x, y;
        gcd(d_slope, h, x, y); // Extended Euclidean algorithm to solve equation
        x += h;
        x = x * d_time % h; // Solution x for ax = b (mod m)
        if (minimize(dis[v], dis[u.i] + x + 1)) // Add 1 for step to move
          pq.push(P(v, dis[v]));
        h *= g; // Restore original H value
      }
  }
  if (dis[n] == INF)
    return -1;
  return dis[n];
}
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ll t;
  cin >> t;
  while (t--)
    cout << solve() << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/