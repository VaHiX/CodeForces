// Problem: CF 808 B - Average Sleep Time
// https://codeforces.com/contest/808/problem/B

/*
 * Problem: Average Sleep Time
 * 
 * Purpose: Calculate the average sleep time over all possible weeks of k consecutive days,
 *          where each day contributes to multiple week averages based on its position.
 * 
 * Algorithm/Techniques: 
 *   - Sliding window technique with weighted contribution.
 *   - Each element a[i] contributes to the sum with a weight equal to how many weeks it is part of.
 *   - For any day at index i (1-based), it is included in min(i, n - i + 1) weeks:
 *     - i weeks from left (including itself)
 *     - (n - i + 1) weeks from right (including itself)
 *   - We compute the total weighted sum and divide by number of weeks: (n - k + 1)
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  double total(0);
  for (long p = 1; p <= n; p++) {
    double x;
    scanf("%lf", &x);
    // Calculate how many weeks the current day contributes to:
    // The weight is the minimum of:
    // - p (number of weeks starting from the beginning up to this day)
    // - (n - p + 1) (number of weeks ending at this day or later)
    double multA = (k < n - k + 1) ? k : (n - k + 1);
    double multB = (p < n - p + 1) ? p : (n - p + 1);
    double mult = (multA < multB) ? multA : multB;
    total += mult * x;
  }
  // Total number of weeks is (n - k + 1)
  double average = total / (n - k + 1);
  printf("%.7lf\n", average);
  return 0;
}


// https://github.com/VaHiX/CodeForces/