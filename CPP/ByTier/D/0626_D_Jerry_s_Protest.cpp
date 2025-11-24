// Problem: CF 626 D - Jerry's Protest
// https://codeforces.com/contest/626/problem/D

/*
 * Problem: Jerry's Protest
 * 
 * Purpose: Calculate the probability that Jerry's sum of three drawn balls is strictly greater
 *          than Andrew's sum, under the condition that Andrew wins the first two rounds and
 *          Jerry wins the third round.
 *
 * Approach:
 * - All possible pairs of balls drawn in each round are generated.
 * - For each pair, the difference is computed and stored in a frequency array `d`.
 * - Cumulative distribution `c` is built from `d` to efficiently compute probabilities.
 * - The required probability is computed using nested loops over differences and cumulative sums.
 *
 * Time Complexity: O(n^2 + MAX_VAL) where n <= 2000 and MAX_VAL <= 5000
 * Space Complexity: O(MAX_VAL) for arrays `d` and `c`, where MAX_VAL = 5000
 */

#include <algorithm>
#include <iostream>
int a[2000];
double d[5000], c[5000];
int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  double ans = 0.0, b = n * (n - 1) / 2;  // b is total number of pairs
  for (int i = 0; i < n; i++)
    std::cin >> a[i];
  std::sort(a, a + n);  // Sort to allow efficient pair generation
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      d[a[j] - a[i]]++;  // Count frequency of each difference
  for (int i = 1; i < 5000; i++)
    d[i] /= b, c[i] = c[i - 1] + d[i];  // Normalize and build cumulative distribution
  for (int i = 1; i < 5000; i++)
    for (int j = 1; j < i; j++)
      ans += d[i] * d[j] * c[i - j - 1];  // Compute final probability using triple nested loop
  std::cout << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/