// Problem: CF 1949 E - Damage per Second
// https://codeforces.com/contest/1949/problem/E

/*
Algorithm: Golden Section Search + Local Optimization
Time Complexity: O(k * n + log(k) * log(k))
Space Complexity: O(n)

The problem involves optimally distributing k skill points between damage per hit (x) and hits per second (y) to minimize the total time to kill all monsters.
We model the total time as a function of damage per hit (x), where hits per second is (k - x). For each monster with health h[i], 
the number of hits needed is ceil(h[i]/x) and the time for that monster is ceil(h[i]/x)/(k-x). 
The total time is the sum of such times for all monsters.

We use a combination of:
1. Golden Section Search or similar local search technique to find optimal x.
2. Evaluate the objective function using a helper function `eval`.
3. Optimize multiple starting points for robustness.
*/
#include <stddef.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#pragma GCC optimize("O2,unroll-loops")
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using uset = unordered_set<T>;
template <class K, class V> using umap = unordered_map<K, V>;
inline void fastio() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}
inline void precision(int k) { cout << fixed << setprecision(k); }
#define iter(x) (x).begin(), (x).end()
#define _f first
#define _s second
const char nl = '\n';
const int INF = (1 << 30) - 1;
const ll LINF = 1e18;
const ld PI = 3.14159265358979323846L;
const ld E = 2.71828182845904523536L;
const ld eps = 1e-7;
#define debug
#ifdef debug
#define dbx(x) cout << x << endl;
#define dbn(x) cout << x << nl;
#define dba(x) cout << x << " ";
#else
#define dbx(x) ;
#define dbn(x) ;
#define dba(x) ;
#endif
const int N = 2e5 + 5;
ll h[N];
ld dp[N];
bool vis[N];
int n, k;
ld eval(int x) {
  ld &res = dp[x];
  if (vis[x])
    return res;
  vis[x] = true;
  for (int i = 0; i < n; i++) {
    res += ceil(h[i] / (ld)x) / ld(k - x); // For each monster, compute time needed
  }
  return res;
}
int check(int s) {
  int l = 1, r = k - 1;
  while (true) {
    int step = max(1, (r - l) / s);
    int x = l;
    for (int i = l; i <= r; i += step) {
      if (eval(i) < eval(x)) {
        x = i;
      }
    }
    if (step == 1)
      return x;
    else {
      l = max(1, x - step);
      r = min(k - 1, x + step);
    }
  }
}
int main() {
  fastio(), precision(10);
  cin >> n >> k;
  ll s = 0;
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }
  int ans = check(500); // Run local search with step size
  for (int i : {4, 7, 9, 57, 87, 100, 200, 319}) { // Try different step sizes for better accuracy
    int r = check(i);
    if (eval(r) < eval(ans))
      ans = r;
  }
  cout << ans << ' ' << k - ans << nl; // Output the chosen damage and hit rates
}


// https://github.com/VaHiX/CodeForces/