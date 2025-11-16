// Problem: CF 1830 B - The BOSS Can Count Pairs
// https://codeforces.com/contest/1830/problem/B

/*
Algorithm: Two-Pointer / Frequency Counting Approach
Time Complexity: O(N * sqrt(N))
Space Complexity: O(N)

The solution uses a frequency counting technique. For each value a[i], we store all b[i] 
values in a bucket indexed by a[i]. Then for each pair (i,j) where i <= j, we check how many 
elements in bucket j match the required value s = i * j - b[i] such that a[i] * a[j] = b[i] + b[j].
We optimize by iterating only up to sqrt(2*N) to avoid redundant checks and handle duplicates carefully.
*/

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = (n) - 1; i >= 0; i--)
#define rep2(i, l, r) for (int i = (l); i < (r); i++)
#define per2(i, l, r) for (int i = (r) - 1; i >= (l); i--)
#define each(e, v) for (auto &e : v)
#define MM << " " <<
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)x.size()
using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
template <typename T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using maxheap = priority_queue<T>;
template <typename T> bool chmax(T &x, const T &y) {
  return (x < y) ? (x = y, true) : false;
}
template <typename T> bool chmin(T &x, const T &y) {
  return (x > y) ? (x = y, true) : false;
}
template <typename T> int flg(T x, int i) { return (x >> i) & 1; }
int pct(int x) { return __builtin_popcount(x); }
int pct(ll x) { return __builtin_popcountll(x); }
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int botbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int botbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
template <typename T> void print(const vector<T> &v, T x = 0) {
  int n = v.size();
  for (int i = 0; i < n; i++)
    cout << v[i] + x << (i == n - 1 ? '\n' : ' ');
  if (v.empty())
    cout << '\n';
}
template <typename T> void printn(const vector<T> &v, T x = 0) {
  int n = v.size();
  for (int i = 0; i < n; i++)
    cout << v[i] + x << '\n';
}
template <typename T> int lb(const vector<T> &v, T x) {
  return lower_bound(begin(v), end(v), x) - begin(v);
}
template <typename T> int ub(const vector<T> &v, T x) {
  return upper_bound(begin(v), end(v), x) - begin(v);
}
template <typename T> void rearrange(vector<T> &v) {
  sort(begin(v), end(v));
  v.erase(unique(begin(v), end(v)), end(v));
}
template <typename T>
vector<int> id_sort(const vector<T> &v, bool greater = false) {
  int n = v.size();
  vector<int> ret(n);
  iota(begin(ret), end(ret), 0);
  sort(begin(ret), end(ret),
       [&](int i, int j) { return greater ? v[i] > v[j] : v[i] < v[j]; });
  return ret;
}
template <typename T> void reorder(vector<T> &a, const vector<int> &ord) {
  int n = a.size();
  vector<T> b(n);
  for (int i = 0; i < n; i++)
    b[i] = a[ord[i]];
  swap(a, b);
}
template <typename T> T floor(T x, T y) {
  assert(y != 0);
  if (y < 0)
    x = -x, y = -y;
  return (x >= 0 ? x / y : (x - y + 1) / y);
}
template <typename T> T ceil(T x, T y) {
  assert(y != 0);
  if (y < 0)
    x = -x, y = -y;
  return (x >= 0 ? (x + y - 1) / y : x / y);
}
template <typename S, typename T>
pair<S, T> operator+(const pair<S, T> &p, const pair<S, T> &q) {
  return make_pair(p.first + q.first, p.second + q.second);
}
template <typename S, typename T>
pair<S, T> operator-(const pair<S, T> &p, const pair<S, T> &q) {
  return make_pair(p.first - q.first, p.second - q.second);
}
template <typename S, typename T>
istream &operator>>(istream &is, pair<S, T> &p) {
  S a;
  T b;
  is >> a >> b;
  p = make_pair(a, b);
  return is;
}
template <typename S, typename T>
ostream &operator<<(ostream &os, const pair<S, T> &p) {
  return os << p.first << ' ' << p.second;
}
struct io_setup {
  io_setup() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
  }
} io_setup;
constexpr int inf = (1 << 30) - 1;
constexpr ll INF = (1LL << 60) - 1;
constexpr int MOD = 998244353;

void solve() {
  int N;
  cin >> N;
  vector<int> a(N), b(N);
  rep(i, N) cin >> a[i];
  rep(i, N) cin >> b[i];
  vector<vector<int>> c(N + 1); // buckets for storing b[i] values grouped by a[i]
  rep(i, N) { c[a[i]].eb(b[i]); } // group b[i] values by a[i]
  rep(i, N + 1) sort(all(c[i])); // sort the buckets
  ll ans = 0;
  vector<int> cnt(N + 1, 0); // frequency count for current bucket
  rep2(i, 1, N + 1) {
    if (1LL * i * i > 2 * N)
      break;
    // Populate the frequency counting for i-th bucket
    each(e, c[i]) cnt[e]++;
    // Iterate over j from i to N
    rep2(j, i, N + 1) {
      if (1LL * i * j > 2 * N)
        break;
      int s = i * j; // target sum
      ll tmp = 0;
      // Count valid combinations using precomputed frequency counts
      each(e, c[j]) {
        if (0 <= s - e && s - e <= N)
          tmp += cnt[s - e];
        if (i == j && e * 2 == s)
          tmp--; // Adjust for duplicates when i == j
      }
      if (i == j)
        tmp /= 2; // Account for double counting
      ans += tmp;
    }
    each(e, c[i]) cnt[e]--; // Remove elements from current bucket for next iteration
  }
  cout << ans << '\n';
}
int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/