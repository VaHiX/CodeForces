// Problem: CF 1141 B - Maximal Continuous Rest
// https://codeforces.com/contest/1141/problem/B

/* 
 * Problem: B. Maximal Continuous Rest
 * Purpose: Find the maximum number of consecutive hours Polycarp rests,
 *          considering that the schedule repeats endlessly.
 * 
 * Algorithms/Techniques:
 *   - Sliding window technique with circular array traversal
 *   - Linear scan through 2*n elements to handle wrap-around cases
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<int> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%d", &a[p]);  // Read the schedule for each hour
  }
  long cnt(0), mx(0);
  for (long p = 0; p < 2 * n; p++) {
    if (a[p % n]) {      // If current hour is a rest hour
      ++cnt;             // Increment current rest streak
      mx = (mx > cnt) ? mx : cnt;  // Update maximum if needed
    } else {
      cnt = 0;           // Reset current streak
    }
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/