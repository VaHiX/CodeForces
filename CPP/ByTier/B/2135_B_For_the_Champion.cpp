// Problem: CF 2135 B - For the Champion
// https://codeforces.com/contest/2135/problem/B

/*
 * Problem: B. For the Champion
 * Algorithm: Binary search on Manhattan distance using four directions
 * Time Complexity: O(n + log(1e9) * 4) = O(n) for preprocessing, O(log(1e9)) for queries
 * Space Complexity: O(n) for storing anchor points
 *
 * The solution uses the fact that Manhattan distance can be transformed into 
 * two linear functions. It finds the two extreme anchor points and makes 
 * strategic moves to determine X and Y by querying the minimum Manhattan 
 * distances from those positions.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
constexpr long long inf = 1e9;
int t, n, x[105], y[105], w1, w2; // w1, w2 hold indices of extreme points
long long t1, t2, t3, val1, val2; // temporary variables for reading results
int main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n), w1 = w2 = 0; // read n, initialize extreme point indices
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &x[i], &y[i]); // read anchor points
      // Find the anchor with maximum (x + y) - this helps determine "upper" bound
      if (!w1 || x[i] + y[i] > x[w1] + y[w1])
        w1 = i;
      // Find the anchor with maximum (x - y) - this helps determine "right" bound
      if (!w2 || x[i] - y[i] > x[w2] - y[w2])
        w2 = i;
    }
    // Query far away in all four directions to get baseline distances
    printf("? U %lld\n? U %lld\n? R %lld\n? R %lld\n", inf, inf, inf, inf),
        fflush(stdout);
    scanf("%lld%lld%lld%lld", &t1, &t2, &t3, &val1), 
        val1 += x[w1] + y[w1] - 4 * inf; // adjust value with known offset
    printf("? D %lld\n? D %lld\n? D %lld\n? D %lld\n", inf, inf, inf, inf),
        fflush(stdout);
    scanf("%lld%lld%lld%lld", &t1, &t2, &t3, &val2),
        val2 += x[w2] - y[w2] - 4 * inf; // adjust value with known offset
    printf("! %lld %lld\n", (val1 + val2) / 2, (val1 - val2) / 2),
        fflush(stdout); // compute and output final coordinates
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/