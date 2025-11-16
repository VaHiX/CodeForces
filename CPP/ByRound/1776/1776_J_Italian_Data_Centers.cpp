// Problem: CF 1776 J - Italian Data Centers
// https://codeforces.com/contest/1776/problem/J

/*
 * Problem: J. Italian Data Centers
 * Algorithm: BFS-based diameter calculation with color-aware transitions
 * Time Complexity: O(n^2 * (n + m)) where n is the number of servers and m is the number of wires
 * Space Complexity: O(n + m) for storing the graph and auxiliary arrays
 *
 * Approach:
 * For each server in the original data center, perform a BFS to compute the shortest distances
 * to all other servers considering color transitions. When colors of two connected servers
 * differ, the transition cost is 1; otherwise the cost is 0. The result is the maximum of
 * the minimum distances considering the k-year growth effect.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const ll NN = 2e5 + 5;
const ll mo = 998244353;
ll n, m, k, a[NN], d[NN][2];
vector<ll> v[NN];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for (ll i = 1; i <= n; i++)
    cin >> a[i];
  for (ll i = 1; i <= m; i++) {
    ll ta, tb;
    cin >> ta >> tb;
    v[ta].pb(tb);
    v[tb].pb(ta);
  }
  ll has = 0;
  for (ll i = 1; i <= n; i++) {
    // Initialize distance array to infinity
    for (ll j = 1; j <= n; j++) {
      d[j][0] = 1e9;
      d[j][1] = 1e9;
    }
    d[i][0] = 0;
    queue<pll> q;
    q.push(mp(i, 0));
    while (!q.empty()) {
      ll u = q.front().fi;
      ll pr = q.front().se;
      q.pop();
      for (auto nx : v[u]) {
        ll pnx = pr;
        // If the colors of u and nx are different, flip the parity of path
        if (a[u] != a[nx])
          pnx = 1 - pnx;
        // If not visited, calculate distance and add to queue
        if (d[nx][pnx] == 1e9) {
          d[nx][pnx] = d[u][pr] + 1;
          q.push(mp(nx, pnx));
        }
      }
    }
    // Calculate the maximum diameter for this source server
    for (ll j = 1; j <= n; j++) {
      // The distance considering k-year growth
      has = max(
          has, min(min(d[j][0] + k, d[j][1] + k), (d[j][0] + k + d[j][1]) / 2));
    }
  }
  cout << has << "\n";
}


// https://github.com/VaHiX/CodeForces/