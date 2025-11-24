// Problem: CF 962 A - Equator
// https://codeforces.com/contest/962/problem/A

/*
 * Code Purpose: Find the first day when the cumulative number of problems solved
 *               reaches at least half of the total problems.
 * 
 * Algorithm: Prefix sum approach.
 *            1. Calculate total number of problems.
 *            2. Iterate through days, maintaining a running sum.
 *            3. On each day, check if the running sum is at least half of total.
 *            4. Return the index of the first such day.
 *
 * Time Complexity: O(n) - single pass through the array
 * Space Complexity: O(n) - for storing the array of problems per day
 */

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n);
  ll s(0);  // Total sum of all problems
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    s += a[p];  // Accumulate total problems
  }
  long t(0), ind(0);  // t: current sum, ind: result index
  for (long p = 0; p < n; p++) {
    t += a[p];  // Add current day's problems to the total
    if (2 * t >= s) {  // Check if we've reached or passed half the total
      ind = p + 1;  // Store 1-based index
      break;
    }
  }
  printf("%ld\n", ind);
  return 0;
}


// https://github.com/VaHiX/CodeForces/