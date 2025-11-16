// Problem: CF 939 C - Convenient For Everybody
// https://codeforces.com/contest/939/problem/C

/*
 * Problem: C. Convenient For Everybody
 * 
 * Purpose: Find the optimal starting hour for a one-hour contest such that 
 * the maximum number of participants from all timezones take part.
 * 
 * Algorithm: 
 * - Use a sliding window technique with prefix sums to calculate the number
 *   of participants for each possible start time.
 * - Duplicate the array to handle wraparound (timezone 1 follows timezone n).
 * - For each potential start time (1 to n), compute how many people can join
 *   by checking valid time ranges in all timezones.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Prefix sum array to efficiently compute ranges
 * - Duplicate array to handle circular time zones
 * - Sliding window over 2*n elements to cover all cyclic shifts
 */

#include <stdio.h>
long long n, a[200005], d[200005], mn, val, ans;
int s, e;
int main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    a[n + i] = a[i];  // Duplicate array to handle wraparound
  }
  scanf("%d %d", &s, &e);
  e--;  // Adjust end time to be inclusive (as per problem logic)
  for (int i = 1; i <= 2 * n; i++) {
    d[i] = d[i - 1] + a[i];  // Build prefix sum array
  }
  for (int i = 1; i <= n; i++) {
    // Calculate number of participants for start time i
    val = d[n + e - i + 1] - d[n + s - 1 - i + 1];
    if (mn < val) {
      mn = val;
      ans = i;
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/