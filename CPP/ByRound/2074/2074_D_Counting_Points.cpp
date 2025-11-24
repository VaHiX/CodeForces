// Problem: CF 2074 D - Counting Points
// https://codeforces.com/contest/2074/problem/D

/*
D. Counting Points
time limit per test2 seconds
memory limit per test256 megabytes

The pink soldiers drew n circles with their center on the x-axis of the plane. Also, they have told that the sum of radii is exactly m.
Please find the number of integer points inside or on the border of at least one circle.

Algorithms/Techniques:
- Brute-force point enumeration within each circle's range
- For each x-coordinate in a circle's range, compute the max y-range and update map with maximum height
- Map is used to store unique x-values and corresponding max y-range (number of integer points vertically)

Time Complexity: O(m * max(r_i)) due to nested loops over all valid x-coordinates and radii.
Space Complexity: O(m) for storing the map of intervals.

Input:
Each test contains multiple test cases. The first line contains the number of test cases t.
The first line of each test case contains two integers n and m.
The second line of each test case contains x1, x2, ..., xn — the centers of the circles.
The third line of each test case contains r1, r2, ..., rn — the radii of the circles.

Output:
For each test case, output the number of integer points satisfying the condition on a separate line.

Example:
input
4
2 3
0 0
1 2
2 3
0 2
1 2
3 3
0 2 5
1 1 1
4 8
0 5 10 15
2 2 2 2
output
13
16
14
52
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>

#define ll long long
using namespace std;

ll t, n, m, x[200010], r[200010];

int main() {
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
      cin >> x[i];
    for (int i = 1; i <= n; i++)
      cin >> r[i];
    
    map<ll, ll> m_map; // Map to store (x-coordinate -> maximum vertical span at that x)
    for (ll i = 1; i <= n; i++) {
      // Iterate over all x-coordinates in the range of circle i
      for (ll j = x[i] - r[i]; j <= x[i] + r[i]; j++) {
        // Compute vertical span at point j
        ll now = floor(sqrt(r[i] * r[i] - (x[i] - j) * (x[i] - j))) * 2 + 1;
        m_map[j] = max(m_map[j], now); // Keep the maximum y-range for overlapping intervals
      }
    }

    ll ans = 0;
    for (const auto &i : m_map) {
      ans += i.second;
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/codeForces/