// Problem: CF 1928 F - Digital Patterns
// https://codeforces.com/contest/1928/problem/F

/*
 * Problem: F. Digital Patterns
 * 
 * Algorithms/Techniques:
 * - Coordinate compression + BIT (Binary Indexed Tree) for range updates and queries
 * - Segment tree-like approach with set tracking of intervals
 * - Efficiently calculates "interestingness" by counting sub-squares without adjacent same values
 * 
 * Time Complexity:
 * - Preprocessing: O(n log n + m log m)
 * - Each query: O(log n + log m)
 * - Total: O((n + m) log(n + m) + q * (log n + log m))
 * 
 * Space Complexity:
 * - O(n + m) for BITs and auxiliary structures
 */

#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const int MAXN = 3e5 + 10;
inline ll u(ll n) { return n; }
inline ll v(ll n) { return n * (n + 1) / 2; }
inline ll w(ll n) {
  return n * (n + 1) * (2 * n + 1) / 6 - n * n * (n + 1) / 2;
}
struct bit {
  int n;
  vector<ll> c;
  bit(int n) : n(n), c(n + 1) {}
  inline void add(int k, ll x) {
    if (k <= 0)
      return;
    for (int i = k; i <= n; i += i & -i)
      c[i] += x;
  }
  inline ll ask(int k) {
    if (k <= 0)
      return 0;
    if (k > n)
      k = n;
    ll res = 0;
    for (int i = k; i; i &= i - 1)
      res += c[i];
    return res;
  }
};
struct maintainer {
  int n;
  bit a, b, c, d;
  maintainer(int n) : n(n), a(n), b(n), c(n), d(n) {}
  inline void insert(int k) {
    a.add(n - k + 1, 1), b.add(n - k + 1, u(k));
    c.add(k, v(k)), d.add(k, w(k));
  }
  inline void erase(int k) {
    a.add(n - k + 1, -1), b.add(n - k + 1, -u(k));
    c.add(k, -v(k)), d.add(k, -w(k));
  }
  inline ll query(int m) {
    return w(m) * a.ask(n - m + 1) + v(m) * b.ask(n - m + 1) +
           u(m) * c.ask(m - 1) + d.ask(m - 1);
  }
};
struct node {
  maintainer &a, &b;
  ll ans;
  vector<int> d;
  set<int> s;
  int id;
  inline void insert(int k) { a.insert(k), ans += b.query(k); }
  inline void erase(int k) { a.erase(k), ans -= b.query(k); }
  node(vector<int> t, maintainer &a, maintainer &b, int id)
      : s(), d(t.size()), a(a), b(b), ans(), id(id) {
    s.insert(0), s.insert(t.size());
    for (int i = 1; i < t.size(); i++) {
      d[i] = t[i] - t[i - 1];
      if (!d[i])
        s.insert(i);
    }
    for (auto it = s.begin(); next(it) != s.end(); ++it)
      insert(*next(it) - *it);
  }
  inline void change(int k, ll x) {
    if (!k || k == a.n)
      return;
    if (!d[k] && d[k] + x) {
      auto it = s.find(k), pre = prev(it), nxt = next(it);
      erase(*it - *pre), erase(*nxt - *it), insert(*nxt - *pre);
      s.erase(it);
    }
    if (d[k] && !(d[k] + x)) {
      auto it = s.insert(k).first, pre = prev(it), nxt = next(it);
      erase(*nxt - *pre), insert(*it - *pre), insert(*nxt - *it);
    }
    d[k] += x;
  }
  inline void add(int l, int r, ll x) { change(l - 1, x), change(r, -x); }
};
int n, m, q;
int main() {
  scanf("%d%d%d", &n, &m, &q);
  vector<int> a(n), b(m);
  for (int &x : a)
    scanf("%d", &x);
  for (int &x : b)
    scanf("%d", &x);
  maintainer ta(n), tb(m);
  node pa(a, ta, tb, 1), pb(b, tb, ta, 2);
  printf("%lld\n", pa.ans + pb.ans);
  for (int t, l, r, x; q--;) {
    scanf("%d%d%d%d", &t, &l, &r, &x);
    t == 1 ? pa.add(l, r, x) : pb.add(l, r, x);
    printf("%lld\n", pa.ans + pb.ans);
  }
}


// https://github.com/VaHiX/CodeForces/