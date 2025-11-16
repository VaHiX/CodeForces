// Problem: CF 1687 A - The Enchanted Forest
// https://codeforces.com/contest/1687/problem/A

/*
 * Problem: A. The Enchanted Forest
 * Algorithms/Techniques: Prefix Sum, Sliding Window
 *
 * Time Complexity: O(n) per test case, where n is the number of points.
 * Space Complexity: O(n), for storing the array a and prefix sums.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
long long i, n, k, s, T, a[200200];
int main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld %lld", &n, &k);
    s = 0;
    // Build prefix sum array: a[i] will store sum of elements from 1 to i
    for (i = 1; i <= n; i++)
      scanf("%lld", &a[i]), a[i] += a[i - 1];
    
    // If total time k is greater than or equal to number of points n,
    // we can take all points and move optimally.
    if (n <= k)
      s = a[n] + n * (n - 1) / 2 + (k - n) * n;
    else
      // Sliding window approach:
      // For each valid window of size k, compute max mushrooms that could be collected
      for (i = k; i <= n; i++)
        s = max(s, a[i] - a[i - k] + k * (k - 1) / 2);
    
    printf("%lld\n", s);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/