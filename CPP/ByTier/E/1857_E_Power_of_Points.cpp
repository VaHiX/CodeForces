// Problem: CF 1857 E - Power of Points
// https://codeforces.com/contest/1857/problem/E

/*
 * Problem: E. Power of Points
 *
 * Purpose: For each point s in the given array x, compute the sum of "power" of
 * all integer points from 1 to 1e9, where the power of a point p is the number
 * of segments [s, x_i] (or [x_i, s] if x_i < s) that contain p.
 *
 * Algorithm:
 *   - Use sorting and prefix sum techniques to efficiently calculate the
 * contribution of each point s.
 *   - For a fixed s = x[i], each segment [s, x_j] contributes to all integer
 * points p such that s <= p <= x_j (if x_j >= s) or x_j <= p <= s (if x_j < s).
 *   - Rearranging the logic allows precomputing the result for all s values
 * using sorted order and prefix sums.
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing arrays and temporary variables.
 */

#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;
using INT = long long;
const int NN = 2e5 + 111;
int x[NN], id[NN];
INT ans[NN];

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    INT sum = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", x + i);
      id[i] = i;
      sum += x[i];
    }
    // Sort indices based on the values of x in ascending order
    sort(id + 1, id + n + 1, [&](int u, int v) { return x[u] < x[v]; });
    INT cur_sum = 0;
    for (int i = 1; i <= n; i++) {
      int u = id[i];   // Get index in original array
      cur_sum += x[u]; // Prefix sum of sorted values
      // Left part: contribution from segments where s = x[u] and x_j <= s
      ans[u] = (INT)x[u] * i - cur_sum;
      // Right part: contribution from segments where s = x[u] and x_j >= s
      ans[u] += sum - cur_sum - (INT)x[u] * (n - i);
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] + n << ' '; // Add n for the offset
    }
    puts("");
  }
}

// https://github.com/VaHiX/CodeForces/