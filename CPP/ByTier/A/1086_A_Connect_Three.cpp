// Problem: CF 1086 A - Connect Three
// https://codeforces.com/contest/1086/problem/A

/*
Algorithm/Technique:
The problem is about finding the minimum number of plots to be cleared such that
all three given points (A, B, C) are connected in a path through adjacent
cleared plots. This is effectively a minimum spanning tree or connectivity
problem in a grid.

The approach:
1. Sort the x and y coordinates of the three points.
2. Find the median x and y values from these sorted coordinates.
3. Connect each point to the median point using horizontal and vertical lines,
effectively forming a "cross" or "plus" shape.
4. Insert all the plots that make up the cross into a set to avoid duplicates.
5. Output the total count and the plots.

Time Complexity: O(1) - Since there are only 3 points, sorting and operations
are constant time. Space Complexity: O(1) - The space used is constant, as we
process only fixed number of points.
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
#define nl "\n"
#define nf endl
#define ll long long
#define pb push_back
#define _ << ' ' <<
#define INF (ll)1e18
#define mod 998244353
#define maxn 110
ll i, i1, j, k, k1, t, n, m, res, flag[10], a, b;
vector<ll> x, y;
vector<array<ll, 2>> v;
set<array<ll, 2>> rs;

// Function to connect two points by clearing the path between them
void cnn(ll x1, ll y1, ll x2, ll y2) {
  ll i;
  // Clear horizontal path from (x1, y1) to (x2, y1)
  for (i = min(x1, x2); i <= max(x1, x2); i++)
    rs.insert({i, y1});
  // Clear vertical path from (x2, y1) to (x2, y2)
  for (i = min(y1, y2); i <= max(y1, y2); i++)
    rs.insert({x2, i});
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  n = 3;
  for (i = 1; i <= n; i++) {
    cin >> a >> b;
    v.pb({a, b});
    x.pb(a);
    y.pb(b);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  // Connect each point to the median point
  for (i = 0; i < n; i++)
    cnn(v[i][0], v[i][1], x[1], y[1]);
  cout << rs.size() << nl;
  for (auto u : rs)
    cout << u[0] _ u[1] << nl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/