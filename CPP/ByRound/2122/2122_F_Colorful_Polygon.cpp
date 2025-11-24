// Problem: CF 2122 F - Colorful Polygon
// https://codeforces.com/contest/2122/problem/F

/*
F. Colorful Polygon
Algorithms/Techniques: Greedy construction using merge process and geometric placement
Time Complexity: O(n^2 log n) due to sorting in the loop
Space Complexity: O(n^2) for storing coordinates of polygon vertices

This solution constructs a simple polygon with at most 333 vertices that has exactly
(a1 + a2 + ... + an)! / (a1! * a2! * ... * an!) different triangulations.

The approach:
- Start with the input array of integers
- Repeatedly merge the two smallest elements
- For each merge operation, we construct a "blossom" shape in the plane
  that contributes to the count of triangulations as described by the multinomial coefficient
- Continue until one element remains
- The final result is a polygon formed by connecting these constructed shapes
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define fi first
#define se second
#define pb push_back
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rng(i, a, b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()
void cincout() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(15);
}
int main() {
  cincout();
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  vector<pii> pts; // Stores the coordinates of polygon vertices
  int c = 0;       // Controls x-coordinate offset for current blossom
  while (a.size() > 1) {
    sort(all(a));         // Sort to find two smallest elements
    int x = a[0], y = a[1]; 
    rep(i, x + 1) pts.pb({c, -i});             // Add vertical line segment for x
    rep(i, y + 1) pts.pb({c + 1, i - y});     // Add vertical line segment for y
    c += 2;                                   // Offset for next blossom
    a.erase(a.begin());   // Remove first smallest element
    a.erase(a.begin());   // Remove second smallest element
    a.pb(x + y);          // Add merged value back
  }
  pts.pb({1000000, 1}); // Endpoint to close the polygon
  cout << pts.size() << '\n';
  for (auto [x, y] : pts) {
    cout << x << ' ' << y << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/