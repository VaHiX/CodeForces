// Problem: CF 2154 F1 - Bombing (Easy Version)
// https://codeforces.com/contest/2154/problem/F1

/*
Algorithm: Dynamic Programming with Combinatorics
Purpose: Count the number of ways to fill -1s in permutation p so that it forms a riffle shuffle of [1,2,...,n]
Time Complexity: O(n^2) per test case
Space Complexity: O(n) for auxiliary arrays

The solution works by:
1. Precomputing combinations using a combinatorics class
2. For each possible split point d (from 2 to n), we simulate the riffle shuffle
3. We count how many ways we can place the -1 values such that the resulting sequence is a valid riffle shuffle
4. The key insight is to track positions where elements are placed (ls1, ls2) and use combinations to count valid arrangements
5. The final answer is the sum of valid combinations across all possible split points
*/

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define eps 1e-6
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
#define fi first
#define se second
#define MOD 998244353
namespace Math {
template <const int mod> struct modint {
  int val;
  static int norm(const int &x) { return x < 0 ? x + mod : x; }
  static constexpr int get_mod() { return mod; }
  bool operator!() { return !val; }
  bool operator<(const modint &o) { return val < o.val; }
  bool operator>(const modint &o) { return val > o.val; }
  bool operator<=(const modint &o) { return val <= o.val; }
  bool operator>=(const modint &o) { return val >= o.val; }
  bool operator==(const modint &o) { return val == o.val; }
  bool operator!=(const modint &o) { return val != o.val; }
  modint() : val(0) {}
  modint(const LL &o) : val(norm(o % mod)) {}
  modint inv() const { return ksm(*this, mod - 2); }
  modint operator+() const { return val; }
  modint operator-() const { return norm(-val); }
  modint &operator++() { return ++val == mod ? val = 0 : val, *this; }
  modint operator++(int) {
    modint t = *this;
    ++val == mod ? 0 : val;
    return t;
  }
  modint &operator--() { return val ? val-- : val = mod - 1, *this; }
  modint operator--(int) {
    modint t = *this;
    val ? val-- : val = mod - 1;
    return t;
  }
  modint &operator+=(const modint &o) {
    return val = val + o.val >= mod ? val + o.val - mod : val + o.val, *this;
  }
  modint &operator-=(const modint &o) {
    return val = val - o.val < 0 ? val - o.val + mod : val - o.val, *this;
  }
  modint &operator*=(const modint &o) {
    return val = 1ll * val * o.val % mod, *this;
  }
  modint &operator/=(modint o) {
    return val = 1ll * val * o.inv().val % mod, *this;
  }
  modint operator+(const modint &o) { return modint(*this) += o; }
  modint operator-(const modint &o) { return modint(*this) -= o; }
  modint operator*(const modint &o) { return modint(*this) *= o; }
  modint operator/(const modint &o) { return modint(*this) /= o; }
  modint operator&(const modint &o) { return val & o.val; }
  modint operator>>(const modint &o) { return val >> o.val; }
  template <typename T> modint friend ksm(modint a, T b) {
    if (b < 0)
      return ksm(a, -b).inv();
    modint res(1);
    for (; b; a *= a, b >>= 1)
      if (b & 1)
        res *= a;
    return res;
  }
  using is = std::istream;
  using os = std::ostream;
  friend is &operator>>(is &i, modint &a) {
    LL v;
    return i >> v, a.val = norm(v % mod), i;
  }
  friend os &operator<<(os &o, const modint &a) { return o << a.val; }
};
using Mint998 = modint<998244353>;
using Mint107 = modint<1000000007>;
template <typename T> struct Comb {
  vector<T> fc, fci, _inv;
  void Init(int N) {
    fc.resize(N + 1), fci.resize(N + 1), _inv.resize(N + 1);
    fc[0] = 1;
    for (int i = 1; i <= N; i++)
      fc[i] = fc[i - 1] * i;
    fci[N] = fc[N].inv();
    for (int i = N - 1; i >= 0; i--)
      fci[i] = fci[i + 1] * (i + 1), _inv[i + 1] = fci[i + 1] * fc[i];
  }
  T C(int n, int m) {
    if (n < m || n < 0 || m < 0)
      return 0;
    return fc[n] * fci[m] * fci[n - m];
  }
};
} // namespace Math
#undef MOD
#define MOD 998244353
using Mint = Math::Mint998;
Math::Comb<Mint> Z;
#define MAXN 300005
int n, p[MAXN];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i];
  Mint ans = 0;
  {
    bool bl = 1;
    for (int i = 1; i <= n; i++)
      if (p[i] != -1 && p[i] != i) {
        bl = 0;
        break;
      }
    if (bl)
      ans -= n - 2;
  }
  for (int d = 2; d <= n; d++) {
    int ct = 0, ls1 = 0, ls2 = d - 1;
    Mint res = 1;
    for (int i = 1; i <= n; i++)
      if (p[i] == -1)
        ct++;
      else if (p[i] < d) {
        res *= Z.C(ct, p[i] - ls1 - 1);
        ls2 += ct - (p[i] - ls1 - 1), ls1 = p[i];
        ct = 0;
      } else {
        res *= Z.C(ct, p[i] - ls2 - 1);
        ls1 += ct - (p[i] - ls2 - 1), ls2 = p[i];
        ct = 0;
      }
    if (ct != n - ls2 + d - 1 - ls1)
      res = 0;
    else
      res *= Z.C(ct, n - ls2);
    ans += res;
  }
  cout << ans << '\n';
}
signed main() {
  Z.Init(5000);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/