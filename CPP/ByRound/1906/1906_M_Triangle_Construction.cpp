// Problem: CF 1906 M - Triangle Construction
// https://codeforces.com/contest/1906/problem/M

/*
M. Triangle Construction

Algorithm/Techniques: Greedy algorithm with prefix sums and maximum element tracking.

The problem asks us to find the maximum number of non-degenerate triangles that can be formed using special points on the sides of a regular N-sided polygon, under constraints that:
- Each point can be used only once.
- Triangles must not intersect (non-degenerate).
- Points on side i are divided into A_i + 1 equal segments.

Key insight:
Each triangle requires 3 distinct points. We want to maximize triangles without using any point more than once and avoiding intersections.

Approach:
We do a greedy selection of triplets from the available special points. To simplify counting, we observe that if we sort all points by their side (in order), we can process them greedily while maintaining validity. 

However, an easier way to compute this is:
- The total number of special points is sum(A_i).
- A triangle needs 3 points.
- For any valid triangle, if we pick points from different sides such that they form a non-degenerate shape, the optimal approach will be based on the minimum of:
   - Total possible triangles using all points: sum(A) / 3
   - Available points minus the maximum side's contribution (to ensure no overlap in greedy assignment)

So we compute:
- Total number of special points (`sm`)
- Maximum number of points on a single side (`mx`)
- Answer = min(sm / 3, sm - mx)

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  long long sm = 0; // Sum of all special points
  int N, x, mx = 0; // N: number of sides, x: current point count, mx: max points on one side
  ios::sync_with_stdio(0);
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> x, sm += x, mx = max(mx, x); // Read A_i and accumulate sum and track maximum
  cout << min(sm / 3, sm - mx) << endl; // Compute the result as per analysis above
}


// https://github.com/VaHiX/codeForces/