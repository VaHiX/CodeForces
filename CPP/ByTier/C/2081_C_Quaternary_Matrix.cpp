/*
 * Problem URL : https://codeforces.com/problemset/problem/2081/C
 * Submit Date : 2025-08-22
 */

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class S>
ostream &operator<<(ostream &o, const pair<T, S> &p) {
  return o << '(' << p.first << ", " << p.second << ')';
}
template <template <class, class...> class T, class... A>
typename enable_if<!is_same<T<A...>, string>(), ostream &>::type
operator<<(ostream &o, T<A...> V) {
  o << '[';
  for (auto a : V)
    o << a << ", ";
  return o << ']';
}

typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pl;
typedef vector<ll> vl;

#define G(x)                                                                   \
  ll x;                                                                        \
  cin >> x;
#define GD(x)                                                                  \
  ld x;                                                                        \
  cin >> x;
#define GS(s)                                                                  \
  string s;                                                                    \
  cin >> s;
#define F(i, l, r) for (ll i = l; i < (r); ++i)
#define FD(i, r, l) for (ll i = r; i > (l); --i)
#define P(a, n)                                                                \
  {                                                                            \
    cout << "{ ";                                                              \
    F(_, 0, n) cout << a[_] << " ";                                            \
    cout << "}\n";                                                             \
  }
#define EX(x)                                                                  \
  {                                                                            \
    cout << x << '\n';                                                         \
    exit(0);                                                                   \
  }
#define A(a) (a).begin(), (a).end()
#define K first
#define V second
#define M 1000000007 // 998244353
#define N 1010

string s[N];
ll r[N], c[N];
vl vr[4], vc[4];

#define AMOGUS(x, y, z)                                                        \
  while (vr[x].size() && vc[y].size() && vc[z].size()) {                       \
    ll i = vr[x].back(), j1 = vc[y].back(), j2 = vc[z].back();                 \
    vr[x].pop_back(), vc[y].pop_back(), vc[z].pop_back();                      \
    s[i][j1] ^= y, s[i][j2] ^= z, ops += 2;                                    \
  }
#define ANOGOS(x, y, z)                                                        \
  while (vc[x].size() && vr[y].size() && vr[z].size()) {                       \
    ll j = vc[x].back(), i1 = vr[y].back(), i2 = vr[z].back();                 \
    vc[x].pop_back(), vr[y].pop_back(), vr[z].pop_back();                      \
    s[i1][j] ^= y, s[i2][j] ^= z, ops += 2;                                    \
  }
#define ABUGGUS(x, y)                                                          \
  while (vr[x].size() && vc[y].size()) {                                       \
    ll i1 = vr[x].back(), j1 = vc[y].back();                                   \
    vr[x].pop_back(), vc[y].pop_back();                                        \
    ll i2 = vr[x].back(), j2 = vc[y].back();                                   \
    vr[x].pop_back(), vc[y].pop_back();                                        \
    s[i1][j1] ^= x ^ y;                                                        \
    s[i1][j2] ^= y;                                                            \
    s[i2][j1] ^= x;                                                            \
    ops += 3;                                                                  \
  }
#define SUSBONGUS(x)                                                           \
  for (ll i : vr[x])                                                           \
    s[i][0] ^= x, ops++;
#define SUSMOGUS(x)                                                            \
  for (ll j : vc[x])                                                           \
    s[0][j] ^= x, ops++;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  G(tc) while (tc--) {
    G(n) G(m) F(i, 0, n) cin >> s[i];
    F(i, 0, n) F(j, 0, m) r[i] ^= (s[i][j] - '0'), c[j] ^= (s[i][j] - '0');
    F(i, 0, n) vr[r[i]].push_back(i);
    F(j, 0, m) vc[c[j]].push_back(j);
    ll ops = 0;
    F(k, 1, 4) while (vr[k].size() && vc[k].size()) {
      ll i = vr[k].back(), j = vc[k].back();
      vr[k].pop_back();
      vc[k].pop_back();
      s[i][j] ^= k;
      ops++;
    }
    AMOGUS(1, 2, 3)
    AMOGUS(2, 3, 1)
    AMOGUS(3, 1, 2)
    ANOGOS(1, 2, 3)
    ANOGOS(2, 3, 1)
    ANOGOS(3, 1, 2)
    ABUGGUS(1, 2)
    ABUGGUS(2, 1)
    ABUGGUS(1, 3)
    ABUGGUS(3, 1)
    ABUGGUS(2, 3)
    ABUGGUS(3, 2)
    SUSBONGUS(1)
    SUSBONGUS(2)
    SUSBONGUS(3)
    SUSMOGUS(1)
    SUSMOGUS(2)
    SUSMOGUS(3)
    cout << ops << '\n';
    F(i, 0, n) cout << s[i] << '\n';
    F(k, 0, 4) vr[k].clear(), vc[k].clear();
    fill_n(r, n, 0);
    fill_n(c, m, 0);
  }
}
