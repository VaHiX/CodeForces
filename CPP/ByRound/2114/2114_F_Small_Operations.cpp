// Problem: CF 2114 F - Small Operations
// https://codeforces.com/contest/2114/problem/F

/*
F. Small Operations
Algorithm: Dynamic Programming with Memoization
Approach:
- For each number x, we recursively find the minimum operations needed to reduce it to 1,
  using divisors up to k.
- The main idea is to factorize x and y by their GCD, then compute the steps for each part.

Time Complexity: O(sqrt(x) * log(max(x, y)) * t), where t is number of test cases
Space Complexity: O(sqrt(x) * log(max(x, y))) due to memoization map

The function `f(x, k)` returns the minimum operations to reduce x to 1, where each step
can either multiply or divide by a factor between 1 and k.
*/

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <utility>

#define mp make_pair
using namespace std;
map<pair<int, int>, int> dp; // Memoization table for f(x, k)

int f(int x, int k) {
  if (x == 1)
    return 0; // Base case: already reduced to 1
  if (dp.find(mp(x, k)) != dp.end())
    return dp[{x, k}]; // Return memoized result if available

  int bnd = sqrt(x), r = 1e8; // Bound for divisors and initialize min steps
  for (int i = 1; i <= bnd; ++i) {
    if (x % i)
      continue; // Skip non-divisors
    int j = x / i;
    if (1 < i && i <= k)
      r = min(r, f(x / i, k) + 1); // Try dividing by i if valid
    if (1 < j && j <= k)
      r = min(r, f(x / j, k) + 1); // Try dividing by j if valid
  }
  return dp[{x, k}] = r; // Store and return the minimum steps
}

signed main() {
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int x, y, k;
    scanf("%d %d %d", &x, &y, &k);
    int g = __gcd(x, y); // Find GCD of x and y
    int a = f(x / g, k) + f(y / g, k); // Compute operations needed for both parts
    a >= 1e8 ? puts("-1") : printf("%d\n", a); // Output result or -1 if impossible
  }
}


// https://github.com/VaHiX/codeForces/