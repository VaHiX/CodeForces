// Problem: CF 1765 J - Hero to Zero
// https://codeforces.com/contest/1765/problem/J

/*
 * Problem: J. Hero to Zero
 * 
 * Purpose:
 *   This code computes the minimum number of coins needed to reduce a matrix c[i][j] = |a[i] - b[j]| to all zeros,
 *   using specific operations that affect rows/columns or individual elements.
 * 
 * Approach:
 *   - The key insight is that we can model the problem as minimizing the sum of absolute differences between a and b,
 *     under certain operations.
 *   - The solution uses a mathematical derivation involving sorted arrays to compute optimal operations.
 *   - The algorithm sorts both arrays and then processes elements to calculate a minimal cost based on cumulative
 *     differences and how elements relate in the sorted order.
 * 
 * Time Complexity:
 *   O(n log n) due to sorting and linear traversal.
 * 
 * Space Complexity:
 *   O(n) for storing arrays a and b.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n), b(n);
  for (int &x : a)
    scanf("%d", &x);
  for (int &x : b)
    scanf("%d", &x);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  ll ans = 0;
  // Compute the base cost using the derived formula involving counts of elements
  for (int i = 0; i < n; i++)
    ans += 1ll * n * (a[i] + b[i]) -
           2ll * a[i] * (b.end() - lower_bound(b.begin(), b.end(), a[i])) -
           2ll * b[i] * (a.end() - upper_bound(a.begin(), a.end(), b[i]));
  // Adjust the result by subtracting over-counted terms related to element differences
  for (int i = 0; i < n; i++)
    ans -= (n - 1ll) * abs(a[i] - b[i]);
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/