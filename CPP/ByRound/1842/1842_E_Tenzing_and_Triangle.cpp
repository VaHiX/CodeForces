// Problem: CF 1842 E - Tenzing and Triangle
// https://codeforces.com/contest/1842/problem/E

/*
Code Purpose:
This code solves the problem of erasing all points on a 2D plane using two operations:
1. Draw a triangle defined by lines x = a, y = b, and x + y = k, with cost l * A where l is the side length.
2. Erase a specific point with cost c_i.

The solution uses dynamic programming with a segment tree to efficiently compute the minimum cost.
The key idea is to process points by their y-coordinate and use a segment tree to maintain the maximum value of optimal
choice at each x-coordinate to determine the best way to cover points using triangles or direct erasure.

Algorithms/Techniques:
- Dynamic Programming
- Segment Tree with Lazy Propagation
- Coordinate Compression
- Greedy approach over y-coordinates

Time Complexity: O(n * log n)
Space Complexity: O(n)
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int M = 1 << 18;
int n, k, A, dp[200001], seg[1 << 19], added[1 << 19];
vector<pair<int, int>> pts[200000]; // Store points grouped by y-coordinate

// Function to update segment tree (used for maintaining max values)
void ins(int p, int u) {
  for (seg[p += M] = u; p > 1; p >>= 1)
    seg[p >> 1] = max(seg[p], seg[p ^ 1]);
}

// Function to update segment tree with lazy propagation
void upd(int p, int u) {
  for (p += M; p > 1; p >>= 1) {
    int v = p & 1 ? u : 0;
    added[p ^ 1] += v, seg[p ^ 1] += v;
    seg[p >> 1] = max(seg[p], seg[p ^ 1]) + added[p >> 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k >> A;
  int sum = 0;
  
  // Read input points, group by y-coordinate, and accumulate sum of point costs
  for (int i = 0, x, y, c; i < n; ++i) {
    cin >> x >> y >> c;
    pts[y].push_back({x, c});
    sum += c;
  }
  
  // Process all y-coordinates from 1 to k, maintaining the maximum coverage 
  // at each coordinate using dynamic programming
  for (int i = 1; i <= k; ++i) {
    // Apply cost of drawing a triangle to current segment
    upd(i, -A);
    
    // For all points with y-coordinate (k - i), add their cost to segments
    for (auto [x, c] : pts[k - i])
      upd(x + 1, c);
    
    // Compute the optimal DP value for this index
    dp[i] = max(dp[i - 1], seg[1]);
    
    // Update segment tree for next iteration
    ins(i, dp[i]);
  }
  
  // Output total cost minus the best coverage found
  cout << sum - dp[k] << '\n';
}


// https://github.com/VaHiX/CodeForces/