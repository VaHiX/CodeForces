// Problem: CF 1984 F - Reconstruction
// https://codeforces.com/contest/1984/problem/F

/*
 * Code Purpose:
 * This solution determines the number of ways to assign 'P' or 'S' to '?'
 * characters in a string such that there exists a valid array of integers
 * within range [-m, m] satisfying the prefix/suffix sum constraints given by
 * the array b.
 *
 * Key Algorithm:
 * - Dynamic Programming with state tracking:
 *   For each position, track valid assignments ('P' or 'S') that can lead to a
 * valid solution.
 * - Prefix/Suffix Sum Constraints:
 *   P means b[i] = sum(a[0..i])
 *   S means b[i] = sum(a[i..n-1])
 * - Optimization:
 *   Use modulo arithmetic to handle large numbers.
 *
 * Time Complexity: O(n^2) where n is the length of the string
 * Space Complexity: O(n) for the DP arrays and auxiliary vectors
 */

#include <algorithm>
#include <assert.h>
#include <bits/std_abs.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define per(i, n) for (int i = (n) - 1; 0 <= i; i--)
#define rep2(i, l, r) for (int i = (l); i < int(r); i++)
#define per2(i, l, r) for (int i = (r) - 1; int(l) <= i; i--)
#define each(e, v) for (auto &e : v)
#define MM << " " <<
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)x.size()
template <typename T> void print(const vector<T> &v, T x = 0) {
  int n = v.size();
  for (int i = 0; i < n; i++)
    cout << v[i] + x << (i == n - 1 ? '\n' : ' ');
  if (v.empty())
    cout << '\n';
}
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T> bool chmax(T &x, const T &y) {
  return (x < y) ? (x = y, true) : false;
}
template <typename T> bool chmin(T &x, const T &y) {
  return (x > y) ? (x = y, true) : false;
}
template <class T>
using minheap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <class T> using maxheap = std::priority_queue<T>;
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
struct Union_Find_Tree {
  vector<int> data;
  const int n;
  int cnt;
  Union_Find_Tree(int n) : data(n, -1), n(n), cnt(n) {}
  int root(int x) {
    if (data[x] < 0)
      return x;
    return data[x] = root(data[x]);
  }
  int operator[](int i) { return root(i); }
  bool unite(int x, int y) {
    x = root(x), y = root(y);
    if (x == y)
      return false;
    data[x] += data[y], data[y] = x;
    cnt--;
    return true;
  }
  int size(int x) { return -data[root(x)]; }
  int count() { return cnt; };
  bool same(int x, int y) { return root(x) == root(y); }
  void clear() {
    cnt = n;
    fill(begin(data), end(data), -1);
  }
};
template <int mod> struct Mod_Int {
  int x;
  constexpr Mod_Int() : x(0) {}
  Mod_Int(int a) : x(a % mod) {
    if (x < 0)
      x += mod;
  }
  Mod_Int(long long a) : x(a % mod) {
    if (x < 0)
      x += mod;
  }
  Mod_Int operator+(const Mod_Int &p) const { return Mod_Int(*this) += p; }
  Mod_Int operator-(const Mod_Int &p) const { return Mod_Int(*this) -= p; }
  Mod_Int operator*(const Mod_Int &p) const { return Mod_Int(*this) *= p; }
  Mod_Int operator/(const Mod_Int &p) const { return Mod_Int(*this) /= p; }
  Mod_Int &operator+=(const Mod_Int &p) {
    if ((x += p.x) >= mod)
      x -= mod;
    return *this;
  }
  Mod_Int &operator-=(const Mod_Int &p) {
    if ((x += mod - p.x) >= mod)
      x -= mod;
    return *this;
  }
  Mod_Int &operator*=(const Mod_Int &p) {
    long long a = x;
    a *= p.x;
    a %= mod;
    x = a;
    return *this;
  }
  Mod_Int &operator/=(const Mod_Int &p) {
    *this *= p.inverse();
    return *this;
  }
  Mod_Int inverse() const {
    assert(x != 0);
    return pow(mod - 2);
  }
  Mod_Int pow(long long k) const {
    Mod_Int now = *this, ret = 1;
    for (; k > 0; k >>= 1) {
      if (k & 1)
        ret *= now;
      now *= now;
    }
    return ret;
  }
  friend ostream &operator<<(ostream &os, const Mod_Int &p) {
    return os << p.x;
  }
  friend istream &operator>>(istream &is, Mod_Int &p) {
    long long a;
    is >> a;
    p = Mod_Int<mod>(a);
    return is;
  }
};
ll mpow(ll x, ll n, ll mod) {
  ll ans = 1;
  x %= mod;
  while (n != 0) {
    if (n & 1)
      ans = ans * x % mod;
    x = x * x % mod;
    n = n >> 1;
  }
  ans %= mod;
  return ans;
}
template <typename T> T modinv(T a, const T &m) {
  T b = m, u = 1, v = 0;
  while (b > 0) {
    T t = a / b;
    swap(a -= t * b, b);
    swap(u -= t * v, v);
  }
  return u >= 0 ? u % m : (m - (-u) % m) % m;
}
ll divide_int(ll a, ll b) {
  if (b < 0)
    a = -a, b = -b;
  return (a >= 0 ? a / b : (a - b + 1) / b);
}
const int MOD = 998244353;
using mint = Mod_Int<MOD>;
const int inf = 1e9;
int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cout << fixed << setprecision(15);
  int T;
  cin >> T;
  while (T--) {
    ll n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<ll> b(n);
    rep(i, n) cin >> b[i];
    bool fl = true;
    ll prev = 0;
    mint ans = 0;
    rep(t, n) {
      if (s[t] != 'P' && m * (n - t) >= abs(b[t])) {
        ll sum = b[t];
        ll sl = (t ? b[t - 1] : 0);
        vector<mint> dp{1, 0}, ndp(2);
        rep2(i, t + 1, n) {
          fill(all(ndp), 0);
          rep(j, 2) rep(k, 2) {
            char nc = (k ? 'P' : 'S');
            if (s[i] != '?' && s[i] != nc)
              continue;
            int pi = i - 2 + j, ni = i - 1 + k;
            ll pv = (j ? b[i - 1] - sl : sum - b[i - 1]);
            ll nv = (k ? b[i] - sl : sum - b[i]);
            if (m * (ni - pi) < abs(pv - nv) ||
                m * (n - 1 - ni) < abs(sum - nv))
              continue;
            ndp[k] += dp[j];
          }
          swap(dp, ndp);
        }
        ans += dp[0] + dp[1];
      }
      if (s[t] == 'S' || abs(b[t] - prev) > m) {
        fl = false;
        break;
      }
      prev = b[t];
    }
    if (fl)
      ans = ans + 1;
    cout << ans << '\n';
  }
}

// https://github.com/VaHiX/CodeForces/