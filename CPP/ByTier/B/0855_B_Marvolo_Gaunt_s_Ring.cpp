// Problem: CF 855 B - Marvolo Gaunt's Ring
// https://codeforces.com/contest/855/problem/B

/*
 * Problem: Marvolo Gaunt's Ring
 * Algorithm: Dynamic Programming with precomputed minimum/maximum arrays
 * 
 * Approach:
 * - We need to find the maximum value of p*a[i] + q*a[j] + r*a[k] such that i <= j <= k.
 * - To optimize this, we precompute:
 *   - left[p]: pair of (min, max) values from a[0] to a[p]
 *   - right[p]: pair of (min, max) values from a[p] to a[n-1]
 * - For each middle element a[j], we choose optimal a[i] and a[k] by taking:
 *   - min a[i] if p < 0, otherwise max a[i]
 *   - min a[k] if r < 0, otherwise max a[k]
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  const int N = 3;
  long n, x, y, z;
  scanf("%ld %ld %ld %ld", &n, &x, &y, &z);
  std::vector<int64_t> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  // Precompute prefix min and max for left array
  std::vector<std::pair<int64_t, int64_t>> left(n);
  left[0].first = left[0].second = a[0];
  for (long p = 1; p < n; p++) {
    left[p].first = (left[p - 1].first < a[p]) ? left[p - 1].first : a[p];  // min so far
    left[p].second = (left[p - 1].second > a[p]) ? left[p - 1].second : a[p]; // max so far
  }
  // Precompute suffix min and max for right array
  std::vector<std::pair<int64_t, int64_t>> right(n);
  right[n - 1].first = right[n - 1].second = a[n - 1];
  for (long p = n - 2; p >= 0; p--) {
    right[p].first = (right[p + 1].first < a[p]) ? right[p + 1].first : a[p];  // min so far
    right[p].second = (right[p + 1].second > a[p]) ? right[p + 1].second : a[p]; // max so far
  }
  // Compute the maximum value
  int64_t total(-5e18);  // Initialize to a very small number
  for (long p = 0; p < n; p++) {
    int64_t cand(0);
    // Take min or max based on sign of p
    if (x < 0) {
      cand += x * left[p].first;
    } else {
      cand += x * left[p].second;
    }
    cand += y * a[p]; // middle element
    // Take min or max based on sign of r
    if (z < 0) {
      cand += z * right[p].first;
    } else {
      cand += z * right[p].second;
    }
    total = (total > cand) ? total : cand;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/