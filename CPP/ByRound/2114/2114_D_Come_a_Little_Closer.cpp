// Problem: CF 2114 D - Come a Little Closer
// https://codeforces.com/contest/2114/problem/D

/*
 * Problem: D. Come a Little Closer
 *
 * Purpose:
 *   Given n monsters on a 10^9 x 10^9 grid, we want to find the minimum number of coins
 *   needed to destroy all monsters by moving one monster at most once and then selecting
 *   a rectangle that contains all remaining monsters.
 *
 * Algorithm:
 *   - For each monster, temporarily remove it from the grid and compute the minimal
 *     rectangle enclosing the remaining monsters in both row and column directions.
 *   - The area of such a rectangle is calculated using max/min row/column values.
 *   - If the optimal rectangle has an area equal to n-1 (i.e., exactly one empty cell),
 *     we add an extra cost based on either length or width (whichever is smaller).
 *   - Time complexity: O(n log n) due to map operations per test case.
 *   - Space complexity: O(n) for storing monsters and maps.
 *
 * Techniques:
 *   - Using std::map to efficiently track row/column counts and their ranges.
 *   - Iterating through all possible single monster removals to find the minimal cost.
 *
 * Input:
 *   First line: number of test cases t.
 *   For each test case:
 *     Line 1: number of monsters n.
 *     Next n lines: x_i, y_i coordinates for each monster.
 *
 * Output:
 *   Minimum number of coins to destroy all monsters in each test case.
 */

#include <cstdio>
#include <map>
#include <vector>
#include <iterator>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> v(n);
    std::map<ll, ll> mr, mc; // mr: row -> count, mc: column -> count
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &v[p].first, &v[p].second);
      ++mr[v[p].first];   // increment row count
      ++mc[v[p].second];  // increment column count
    }
    if (n == 1) {
      puts("1");
      continue;
    }
    ll ans(1e18 + 7); // Initialize with large value for minimum tracking
    
    for (ll p = 0; p < n; p++) {
      ll row = v[p].first;
      ll col = v[p].second;
      
      --mr[row];           // Temporarily remove this row from consideration
      if (!mr[row]) {      // If no more monsters in this row, erase from map
        mr.erase(row);
      }
      --mc[col];           // Temporarily remove this column
      if (!mc[col]) {
        mc.erase(col);
      }

      // Compute width and height of minimal enclosing rectangle with remaining monsters
      ll length = (mr.rbegin()->first) - (mr.begin()->first) + 1;
      ll width = (mc.rbegin()->first) - (mc.begin()->first) + 1;
      
      ll tst = length * width; // Area of rectangle

      // Special case for when area equals n-1, we add a penalty term
      if (tst == n - 1) {
        tst += (length < width ? length : width);
      }
      
      ans = (ans < tst ? ans : tst); // Keep minimum cost

      ++mr[row];           // Restore original state before next iteration
      ++mc[col];
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/