// Problem: CF 1990 E1 - Catch the Mole(Easy Version)
// https://codeforces.com/contest/1990/problem/E1

/*
 * Problem: Catch the Mole (Easy Version)
 *
 * Algorithm:
 * - Use a two-phase approach to locate the mole:
 *   1. First, find the approximate location of the mole using a DFS-based
 * search, where we traverse down the tree trying to find a subtree containing
 * the mole.
 *   2. Then, use binary search on the path from the found node to the root to
 * pinpoint the exact location of the mole.
 *
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) for storing tree structure and auxiliary arrays
 *
 * Techniques:
 * - Tree traversal with DFS
 * - Binary search on path from node to root
 * - Interactive problem handling with query limits
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define yn_(ans) printf("%s\n", (ans) ? "Yes" : "No");
#define YN_(ans) printf("%s\n", (ans) ? "YES" : "NO");
#define for2(i, n) for (int i = 0; i < int(n); i++)
#define for3(i, m, n) for (int i = int(m); i < int(n); i++)
#define for4(i, m, n, s) for (int i = int(m); i < int(n); i += s)
#define rfor2(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define rfor3(i, m, n) for (int i = int(n) - 1; i >= int(m); i--)
#define rfor4(i, m, n, s) for (int i = int(n) - 1; i >= int(m); i -= s)
#define fi first
#define se second
#define all(X) X.begin(), X.end()
#define rall(X) X.rbegin(), X.rend()
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
using ll = long long;
const int maxn = 2e5 + 10;
const int base = 31337;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const int mod = mod2;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3fll;
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vl = vector<ll>;
using vii = vector<vector<int>>;
template <typename T> T chmax(T &a, T b) { return a > b ? a : (a = b); }
template <typename T> T chmin(T &a, T b) { return a < b ? a : (a = b); }
#define TESTS                                                                  \
  int t;                                                                       \
  cin >> t;                                                                    \
  while (t--)
#define TEST
int __FAST_IO__ = []() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

void sol() {
  int i, n;
  cin >> n;
  vector<vector<int>> G(n + 1);
  for (i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    G[v].push_back(u), G[u].push_back(v);
  }
  vector<int> d(n + 1, 0), h(n + 1, 0), par(n + 1, 0);
  function<void(int, int, int)> dfs;
  dfs = [&](int u, int p, int td) {
    par[u] = p;
    h[u] = 1;
    for (auto v : G[u])
      if (v != p) {
        dfs(v, u, td + 1);
        h[u] = max(h[u], h[v] + 1);
      }
  };
  dfs(1, 1, 0);
  int ZZ = 0;
  int MZ = 100;
  function<void(int, int)> ask1;
  auto QQ = [&](int x) {
    cout << "? " << x << endl;
    cout.flush();
    int rx;
    cin >> rx;
    if (rx == 0)
      ZZ++;
    return rx;
  };
  int lvv = 0;
  ask1 = [&](int u, int p) {
    if (lvv > 0)
      return;
    if (ZZ >= MZ)
      return;
    int sub = 0;
    vector<int> ok;
    for (auto v : G[u])
      if (v != p && h[v] > ZZ) {
        ok.push_back(v);
      }
    if (ok.size() > 1) {
      for (auto v : ok) {
        if (h[v] <= ZZ)
          continue;
        int r = QQ(v);
        if (r == 1) {
          sub = v;
          break;
        }
      }
    } else if (ok.size() == 1)
      sub = ok[0];
    if (sub == 0)
      lvv = u;
    else
      ask1(sub, u);
  };
  ask1(1, 1);
  vector<int> T;
  for (i = lvv; i != 1; i = par[i]) {
    T.push_back(i);
  }
  T.push_back(1);
  reverse(T.begin(), T.end());
  int lo = 0, hi = T.size() - 1;
  while (lo < hi) {
    int md = lo + (hi - lo + 1) / 2;
    if (QQ(T[md]))
      lo = md;
    else {
      hi = md - 1;
      hi--;
      lo--;
      hi = max(0, hi);
      lo = max(0, lo);
    }
  }
  cout << "! " << T[lo] << endl;
  cout.flush();
}
int main() {
  TESTS { sol(); }
  return 0;
}

// https://github.com/VaHiX/CodeForces/