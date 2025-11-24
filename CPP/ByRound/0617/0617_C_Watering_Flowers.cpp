// Problem: CF 617 C - Watering Flowers
// https://codeforces.com/contest/617/problem/C

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <utility>
using namespace std;

typedef long long lr;
lr n, a, b, c, d, x, y, mx, mn;
pair<lr, lr> p[2020];
int main() {
  cin >> n >> a >> b >> c >> d;
  for (lr i = 1; i <= n; ++i) {
    cin >> x >> y;
    p[i] = make_pair((x - a) * (x - a) +
                         (y - b) * (y - b), // Distance squared from fountain 1
                     (x - c) * (x - c) +
                         (y - d) * (y - d)); // Distance squared from fountain 2
  }
  sort(p + 1, p + 1 + n),
      mn = p[n].first; // Sort by distance to fountain 1, initialize mn
  for (lr i = n; i; --i)
    mx = max(mx, p[i].second),
    mn = min(mn,
             p[i - 1].first +
                 mx); // For each flower, calculate minimum sum of r1^2 + r2^2
  cout << mn;
}
// **Problem Title:** C. Watering Flowers
// **Purpose:** Given two fountains and n flowers, determine the minimum sum of
// squared radii (r1² + r2²) such that all flowers are watered by either
// fountain 1 or fountain 2.
// **Algorithm:**
// - For each flower, compute squared distances to both fountains.
// - Sort flowers by distance to fountain 1.
// - Iterate from the furthest to closest flower to determine optimal r1 and r2
// using a greedy approach.
// - Maintain the maximum r2 needed from current flower backward and compute the
// minimal total sum.

// **Time Complexity:** O(n log n) due to sorting
// **Space Complexity:** O(n) for storing flower distances

// **Techniques Used:**
// - Sorting
// - Greedy approach
// - Pairwise squared distance calculation
// - Prefix maximum computation

// https://github.com/VaHiX/CodeForces/