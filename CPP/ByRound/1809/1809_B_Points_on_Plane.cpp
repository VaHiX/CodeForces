// Problem: CF 1809 B - Points on Plane
// https://codeforces.com/contest/1809/problem/B

/*
B. Points on Plane

Algorithm: Binary Search + Mathematical Analysis
Time Complexity: O(log n) per test case
Space Complexity: O(1)

This problem asks us to place n chips on a 2D grid such that:
- Each chip is placed at integer coordinates (x, y)
- The cost of placing a chip at (x, y) is |x| + |y|
- All pairs of chips must be strictly more than distance 1 apart
- We want to minimize the maximum cost among all chips

Key Insight:
We can think about how many chips we can place with a certain cost k.
For any point (x, y), the cost is |x| + |y|. So, for cost k, points must be such that |x| + |y| ≤ k.
This defines a diamond shape centered at origin with vertices at (0,k), (k,0), (0,-k), (-k,0).
But since we also require distance > 1 between chips, we can place at most k^2 points in the area.
We are looking for minimum k such that number of valid points >= n.

Approach:
We binary search on the cost k. For a given k, count how many points (x, y) satisfy:
- |x| + |y| <= k, and
- All pairs have Euclidean distance > 1.

Since all valid points are bounded in diamond of size k, we can calculate number of integer points with cost at most k.
Each such point must be within a diamond region.

The number of lattice points (with cost at most k) that can be placed on a grid with mutual distance > 1 is approximately k^2.
However, this requires careful combinatorics. In simpler terms we note:
- If total valid points with cost <= k are >= n, then we might have a suitable k.

So we binary search on k and find the minimal value.
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll left(0), right(1e9), res(0);
    while (left <= right) {
      ll mid = (left + right) / 2;
      if (mid * mid < n) {  // This condition checks if we can place at least 'n' points within diamond of cost <= mid
        res = mid;         // Store potential answer
        left = mid + 1;    // Try higher costs
      } else {
        right = mid - 1;   // Try lower costs
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/