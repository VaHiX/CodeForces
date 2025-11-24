// Problem: CF 1824 D - LuoTianyi and the Function
// https://codeforces.com/contest/1824/problem/D

/*
 * Problem: LuoTianyi and the Function
 * Algorithms: Mo's Algorithm with Fenwick Tree, Coordinate Compression
 *
 * Time Complexity: O((n + q) * sqrt(n) * log(n))
 * Space Complexity: O(n * sqrt(n) + q)
 *
 * The solution uses a modified Mo's algorithm with a Fenwick tree that supports
 * range updates and queries on linear polynomials. For each element in the
 * array, we maintain a set of positions and use coordinate compression to
 * efficiently compute the g(i,j) values.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <iterator>
#include <random>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T> using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
clock_t startTime;
double getCurrentTime() {
  return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
template <typename T, int D> struct SmallPoly {
  array<T, D + 1> a;
  SmallPoly() {
    for (int i = 0; i <= D; i++)
      a[i] = T();
  }
  SmallPoly(array<T, D + 1> _a) : a(_a) {}
  SmallPoly &operator+=(const SmallPoly &P) {
    for (int i = 0; i <= D; i++)
      a[i] += P.a[i];
    return *this;
  }
  SmallPoly &operator-=(const SmallPoly &P) {
    for (int i = 0; i <= D; i++)
      a[i] -= P.a[i];
    return *this;
  }
  SmallPoly &operator*=(const ll &k) {
    for (int i = 0; i <= D; i++)
      a[i] *= k;
    return *this;
  }
  SmallPoly operator+(const SmallPoly &P) const {
    return SmallPoly(*this) += P;
  }
  SmallPoly operator-(const SmallPoly &P) const {
    return SmallPoly(*this) -= P;
  }
  SmallPoly operator*(const ll &k) const { return SmallPoly(*this) *= k; }
  T eval(const ll &x) const {
    T y = T();
    for (int i = D; i >= 0; i--)
      y = y * x + a[i];
    return y;
  }
};
using Linear = SmallPoly<ll, 1>;
using Item = SmallPoly<Linear, 1>;
template <typename T> struct Fenwick {
  vector<T> a;
  int n;
  Fenwick() : a(), n(0) {}
  Fenwick(int _n) {
    n = _n;
    a = vector<T>(n, T());
  }
  void clear() { a = vector<T>(n, T()); }
  void add(int p, T x) {
    for (; p < n; p |= p + 1)
      a[p] += x;
  }
  T get(int r) {
    if (r < 0)
      return T();
    r = min(r, n - 1);
    T res = T();
    for (; r >= 0; r = (r & (r + 1)) - 1)
      res += a[r];
    return res;
  }
  T getSum(int l, int r) { return get(r - 1) - get(l - 1); }
};
Fenwick<Item> fenv;
int n, m;
const int N = (int)1e6 + 8;
int a[N + 5];
int lst[N + 5];
ll ANS[N + 5];
vector<array<int, 4>> Q[N + 5];
set<int> setik;
Linear replaceBy(ll x, ll y, ll t) { return Linear({-t, 1}) * (y - x); }
Linear getSum(int l, int r) {
  return fenv.get(r - 1).eval(r - 1) - fenv.get(l - 1).eval(l - 1);
}
void addOnSegm(int l, int r, const Linear &L) {
  fenv.add(l, Item({L * (ll)(1 - l), L}));
  fenv.add(r, Item({L * (ll)(1 - r), L}) * (-1));
}
int main() {
  startTime = clock();
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }
  fenv = Fenwick<Item>(n + 1);
  for (int i = 0; i < m; i++) {
    int l1, r1, l2, r2;
    scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
    l1--;
    l2--;
    if (l1 >= r2)
      continue;
    l2 = max(l1, l2);
    r1 = min(r1, r2);
    assert(l1 < r1 && l2 < r2);
    Q[l2].push_back({l1, r1, -1, i});
    Q[r2].push_back({l1, r1, 1, i});
  }
  for (int i = 0; i < n; i++)
    lst[i] = -1;
  setik.insert(-1);
  for (int i = 0; i <= n; i++) {
    for (auto t : Q[i]) {
      ANS[t[3]] += t[2] * getSum(t[0], t[1]).eval(i);
    }
    if (i == n)
      break;
    setik.insert(i);
    if (lst[a[i]] != -1) {
      int p = lst[a[i]];
      auto it = setik.lower_bound(p);
      assert(it != setik.end() && *it == p);
      int nxt = *next(it);
      int prv = *prev(it);
      setik.erase(p);
      addOnSegm(prv + 1, p + 1, replaceBy(p, nxt, i));
    }
    lst[a[i]] = i;
    addOnSegm(i, i + 1, replaceBy(0, i, i) + Linear({-i, 1}));
  }
  for (int i = 0; i < m; i++)
    printf("%lld\n", ANS[i]);
  return 0;
}

// https://github.com/VaHiX/CodeForces/