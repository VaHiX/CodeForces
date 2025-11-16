// Problem: CF 808 E - Selling Souvenirs
// https://codeforces.com/contest/808/problem/E

/*
Code Purpose:
This program solves the problem of selecting souvenirs to maximize total cost under a weight constraint.
It uses a dynamic programming approach with a custom sorting strategy to efficiently compute the optimal subset.
The algorithm sorts items based on a ratio-based comparison to prioritize items with higher value-to-weight ratios,
then applies a modified knapsack DP with space optimization.

Time Complexity: O(n * m) where n is number of souvenirs and m is maximum weight capacity
Space Complexity: O(m) for the DP array

Algorithms/Techniques:
- Custom sorting using a ratio-based comparator
- Space-optimized 0-1 Knapsack Dynamic Programming
- Sliding window update of DP array for efficiency
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1e5 + 5;
struct Node {
  long long x, y;
  bool operator<(const Node &a) const { return y * a.x > x * a.y; }
} a[N];
int n, m, maxx;
long long ans, f[N * 3];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%lld%lld", &a[i].x, &a[i].y);
  std::sort(a + 1, a + 1 + n);  // Sort items by value-to-weight ratio in descending order
  for (int i = 1; i <= n; i++) {
    // Loop from max possible weight down to minimum possible weight to avoid recomputation
    for (int j = std::min(maxx + 3, m); j >= std::max(maxx - 3, (int)a[i].x); j--)
      f[j] = max(f[j - a[i].x] + a[i].y, f[j]);  // Update DP states
    if (maxx < m)
      maxx += a[i].x;  // Increase the effective max weight considered so far
  }
  for (int i = 1; i <= m; i++)
    ans = std::max(ans, f[i]);  // Find maximum value in DP array
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/