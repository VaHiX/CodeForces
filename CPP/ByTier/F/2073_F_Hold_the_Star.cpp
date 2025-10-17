// Problem: CF 2073 F - Hold the Star
// https://codeforces.com/contest/2073/problem/F

/*
 * Problem: Hold the Star
 * Algorithms/Techniques: Convex Hull Trick (CHT), Sweep Line, Optimization with Stack and Sorting
 *
 * Time Complexity: O((M + Q) * log(M) + Q * log(Q))
 * Space Complexity: O(M + Q)
 *
 * Description:
 * This solution solves a game optimization problem where characters move in a line of rooms to 
 * pick up and deliver a star to a specific character. The goal is to minimize the total staracips.
 * Uses Convex Hull Trick (CHT) for efficient dynamic programming updates and queries,
 * along with pre-processing and sweep techniques to optimize performance.
 */

#include <bits/std_abs.h>
#include <limits.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> bool chmin(T &a, const T b) {
  return a > b && (a = b, true);
}
const ll INF = LLONG_MAX / 3;
struct Line {
  mutable ll a, b, p;
  bool operator<(Line o) const { return a < o.a; }
  bool operator<(ll x) const { return p < x; }
};
ll div_floor(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
struct CHT : multiset<Line, less<>> {
  bool isct(iterator x, iterator y) {
    if (y == end())
      return x->p = INF, 0;
    if (x->a == y->a)
      x->p = x->b > y->b ? INF : -INF;
    else
      x->p = div_floor(y->b - x->b, x->a - y->a);
    return x->p >= y->p;
  }
  void add(ll a, ll b) {
    auto z = insert({a, b, 0}), y = z++, x = y;
    while (isct(y, z))
      z = erase(z);
    if (x != begin() && isct(--x, y))
      isct(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) {
      isct(x, erase(y));
    }
  }
  ll max(ll x) {
    auto l = *lower_bound(x);
    return l.a * x + l.b;
  }
};
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  rep(i, 0, t) solve();
}
void solve() {
  ll N;
  int M, Q;
  cin >> N >> M >> Q;
  vector<pair<ll, ll>> p(M);
  rep(i, 0, M) { cin >> p[i].first >> p[i].second; }
  int root = -1;
  {
    auto tmp = p.back();
    sort(all(p));
    rep(i, 0, M) if (tmp == p[i]) root = i;
  }
  vector<ll> L(Q);
  rep(i, 0, Q) cin >> L[i];
  vector<ll> ans(Q);
  rep(i, 0, Q) { ans[i] = p[root].second * abs(p[root].first - L[i]); }
  auto f = [&]() -> void {
    vector<int> order_L(Q);
    rep(i, 0, Q) order_L[i] = i;
    sort(all(order_L), [&](int l, int r) { return L[l] < L[r]; });
    vector<ll> val(M);
    stack<int> st;
    st.push(root);
    rep(i, root + 1, M) {
      while ((int)st.size() != 1 && p[st.top()].second >= p[i].second) {
        st.pop();
      }
      val[i] = val[st.top()] + (p[i].first - p[st.top()].first) * p[i].second;
      st.push(i);
    }
    int ind = M - 1;
    ll tmp = INF;
    for (int rp = Q - 1; rp >= 0; rp--) {
      int id = order_L[rp];
      if (L[id] < p[root].first)
        break;
      while (ind != -1 && p[ind].first >= L[id]) {
        chmin(tmp, val[ind--]);
      }
      chmin(ans[id], tmp);
    }
    CHT C;
    int st_ind = 0;
    while (st_ind != Q && L[order_L[st_ind]] <= p[root].first)
      st_ind++;
    rep(i, 0, root) {
      C.add(-2ll * p[i].second, +(p[root].first + p[i].first) * p[i].second);
    }
    ind = root;
    rep(rp, st_ind, Q) {
      int id = order_L[rp];
      while (ind != M && p[ind].first < L[id]) {
        C.add(-2ll * p[ind].second,
              2ll * p[ind].second * p[ind].first - val[ind]);
        ind++;
      }
      if (ind)
        chmin(ans[id], -C.max(L[id]));
    }
  };
  rep(rp, 0, 2) {
    root = M - 1 - root;
    rep(i, 0, M) { p[i].first = N - p[i].first; }
    reverse(all(p));
    rep(i, 0, Q) L[i] = N - L[i];
    f();
  }
  for (auto x : ans) {
    cout << x << "\n";
  }
}


// https://github.com/VaHiX/codeForces/