// Problem: CF 2165 E - Rainbow Branch
// https://codeforces.com/contest/2165/problem/E

/*
 * Problem: Rainbow Branch
 * Purpose: Assign colors to edges of a tree to minimize the maximum number of colors
 *          on any path between two vertices, for all k from 1 to n-1.
 *
 * Algorithm:
 * - For each k from 1 to n-1, we compute the minimum inconvenience achievable.
 * - This involves finding a coloring strategy that uses exactly k colors and minimizes the maximum
 *   number of distinct colors along any path in the tree.
 * - The key idea is to use tree properties and BFS to calculate distances from leaves,
 *   then process the structure to determine how to assign colors to minimize inconvenience.
 *
 * Time Complexity: O(n log n) per test case due to sorting and processing steps.
 * Space Complexity: O(n) for storing the tree structure, distances, and auxiliary arrays.
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <utility>
#include <vector>

#pragma GCC optimize("O3")
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define MOD 998244353LL
#define INF 1000000001LL
#define POT (1LL << 20)
#define INFL 1000000000000000099LL
#define pii pair<ll, ll>
#define ppi pair<pii, ll>
#define pip pair<ll, pii>
#define ppp pair<pii, pii>
#define vi vector<ll>
#define vii vector<pii>
#define vvi vector<vi>
#define al(x) x.begin(), x.end()
#define rev(x) reverse(al(x))
#define X 18
template <typename T, typename U>
pair<T, U> operator+(const pair<T, U> &a, const pair<T, U> &b) {
  return {a.first + b.first, a.second + b.second};
}
template <typename T, typename U>
pair<T, U> operator-(const pair<T, U> &a, const pair<T, U> &b) {
  return {a.first - b.first, a.second - b.second};
}
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << "{" << p.ff << ", " << p.ss << "}";
  return os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i)
      os << ", ";
    os << v[i];
  }
  os << "}";
  return os;
}
ll fct[1000007];
ll fp(ll a, ll b) {
  ll c = 1;
  while (b) {
    if (b & 1)
      c = (c * a) % MOD;
    a = (a * a) % MOD;
    b /= 2;
  }
  return c;
}
ll iv(ll a) { return fp(a, MOD - 2); }
ll bnm(ll a, ll b) {
  if (b > a || a < 0)
    return 0;
  return ((fct[a] * iv(fct[b])) % MOD * iv(fct[a - b])) % MOD;
}
vi g[300007]; // Adjacency list representation of tree
ll bs[300007], st[300007]; // bs stores distance from leaf, st stores degree of each node
ll n, a, b;
void solve() {
  cin >> n;
  for (ll i = 1; i <= n; i++) {
    g[i].clear();
    bs[i] = 0;
    st[i] = 0;
  }
  for (ll i = 1; i < n; i++) {
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
    st[a]++;
    st[b]++;
  }
  queue<ll> q;
  for (ll i = 1; i <= n; i++) {
    if (st[i] == 1)
      q.push(i);
  }
  bool odw[n + 1];
  for (ll i = 1; i <= n; i++)
    odw[i] = 0;
  while (q.size()) {
    ll c = q.front();
    q.pop();
    odw[c] = 1;
    for (ll i : g[c]) {
      if (!odw[i]) {
        st[i]--;
        if (st[i] == 1)
          q.push(i);
        bs[i] = bs[c] + 1; // Compute distance from nearest leaf
      }
    }
  }
  vi v;
  for (ll i = 1; i <= n; i++)
    v.pb(bs[i]);
  sort(al(v));
  vi v2 = {1};
  for (ll i = 1; i < v.size(); i++) {
    if (v[i] == v[i - 1])
      v2.back()++;
    else
      v2.pb(1);
  }
  vi mx;
  for (ll i = 0; i <= v.back(); i++)
    mx.pb(0);
  for (ll i = 1; i <= n; i++) {
    map<ll, ll> p; // Count nodes at each distance for current node
    for (ll j : g[i]) {
      p[-bs[j]]++; 
    }
    ll sm = 0;
    for (auto k : p) {
      sm += k.ss;
      mx[-k.ff] = max(mx[-k.ff], sm - 1); 
    }
  }
  cout << 1 << " "; // Minimum inconvenience for k=1 is 1
  vi v3;
  for (ll i = v2.size() - 2; i >= 0; i--) {
    mx[i] = max(mx[i], mx[i + 1]); // Update suffix max
  }
  for (ll i = 0; i < v2.size(); i++) {
    for (ll j = 0; j < mx[i]; j++)
      v3.pb(i * 2 + 2); // Append values based on computed thresholds
    for (ll j = mx[i]; j < v2[i]; j++)
      v3.pb(i * 2 + 3);
  }
  v3.pop_back();
  v3.pop_back();
  for (ll i : v3)
    cout << i << " ";
  cout << "\n";
}
int main() {
  fct[0] = 1;
  for (ll i = 1; i < 1000007; i++)
    fct[i] = (fct[i - 1] * i) % MOD;
  ll t = 1;
  cin >> t;
  for (ll i = 1; i <= t; i++) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/