// Problem: CF 1408 D - Searchlights
// https://codeforces.com/contest/1408/problem/D

/*
D. Searchlights

Task: Given n robbers and m searchlights, determine the minimum number of moves to make the configuration safe.
Each move allows shifting all robbers either right (increase a_i) or up (increase b_i).
A configuration is safe if no searchlight can see any robber.

Algorithms/Techniques:
- Dynamic Programming with Prefix Max
- Coordinate Compression

Time Complexity: O(n * m + MAX_COORD)
Space Complexity: O(MAX_COORD)

*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#define ios                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define ll long long
#define endl '\n'
#define pii pair<ll int, ll int>
#define all(a) (a).begin(), (a).end()
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define repi(i, n) for (ll i = 0; i < n; i++)
#define rep(i, a, b) for (ll i = a; i <= b; i++)
#define M 1000000007
#define INF 1e18
using namespace std;

int main() {
  ios;
  ll n, m;
  cin >> n >> m;
  vector<pair<ll, ll>> robbers(n), lights(m);
  repi(i, n) cin >> robbers[i].F >> robbers[i].S; // Read robber coordinates
  repi(i, m) cin >> lights[i].F >> lights[i].S;   // Read light coordinates
  vector<ll> dx(1e6 + 1, 0);                      // DP array to store max needed moves for each offset
  for (auto r : robbers) {                        // For each robber
    for (auto l : lights) {                       // Check against all lights
      ll dy = l.S - r.S + 1;                      // Vertical distance from robber to light
      if (l.F - r.F >= 0)                         // If light is to the right of robber
        dx[l.F - r.F] = max(dx[l.F - r.F], dy);   // Update maximum required vertical moves at this horizontal offset
    }
  }
  ll ans = 1e9;                              // Initialize answer with large value
  for (ll i = 1e6 - 1; i >= 0; i--) {        // Traverse from right to left
    dx[i] = max(dx[i], dx[i + 1]);           // Propagate maximum values forward
    ans = min(ans, dx[i] + i);               // Calculate minimum total moves (horizontal + vertical)
  }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/codeForces/