// Problem: CF 839 A - Arya and Bran
// https://codeforces.com/contest/839/problem/A

/*
 * Problem: Arya and Bran
 * Purpose: Determine the minimum number of days required for Arya to give Bran at least k candies,
 *          given that each day she can find some candies and give at most 8 candies per day.
 * 
 * Algorithm:
 *   - Simulate the process day by day.
 *   - For each day, add the candies found to the total.
 *   - Decide how many candies to give Bran (up to 8).
 *   - Accumulate the number of candies given.
 *   - Stop when the accumulated candies reach at least k.
 * 
 * Time Complexity: O(n), where n is the number of days.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  const int M = 8;  // Maximum candies that can be given per day
  long n, k;
  scanf("%ld %ld", &n, &k);
  long s(0), total(0), days(-1);  // s: candies given, total: candies owned, days: result
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    // Calculate how many candies to give today: min(found_candies, max_per_day)
    long y = x + (total > s) * (total - s);
    y = (y < M) ? y : M;
    total += x;  // Add newly found candies to total
    s += y;      // Add given candies to total given
    if (s >= k) {
      days = p;  // Record day when goal is reached
      break;
    }
  }
  printf("%ld\n", days);
  return 0;
}


// https://github.com/VaHiX/CodeForces/