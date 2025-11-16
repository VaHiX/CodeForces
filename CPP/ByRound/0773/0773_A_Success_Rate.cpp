// Problem: CF 773 A - Success Rate
// https://codeforces.com/contest/773/problem/A

/*
 * Problem: Success Rate
 * 
 * Purpose: Given current successful submissions (x) out of total (y), and a favorite success rate p/q,
 *          determine the minimum number of additional submissions needed to make the success rate equal to p/q.
 * 
 * Algorithm: Binary search on the number of total submissions to make.
 *            For each candidate total submissions (mid), compute:
 *            - s = mid * p - x (additional successful submissions needed)
 *            - t = mid * q - y (additional total submissions needed)
 *            Check if s >= 0 and t >= s to ensure valid configuration.
 *            If valid, try smaller values (move right), else try larger values (move left).
 * 
 * Time Complexity: O(t * log(1e9)) where t is number of test cases.
 * Space Complexity: O(1) - only using a few integer variables.
 */

#include <stdint.h>
#include <cstdio>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int64_t x, y, p, q;
    scanf("%lld %lld %lld %lld", &x, &y, &p, &q);
    int64_t left(1), right(1e9), res(-1);
    while (left <= right) {
      int64_t mid = (left + right) / 2;
      int64_t s = mid * p - x;      // Additional successful submissions needed
      int64_t t = mid * q - y;      // Additional total submissions needed
      if ((s >= 0) && (t >= s)) {   // Check if valid configuration
        res = t;                    // Store the result
        right = mid - 1;            // Try smaller value
      } else {
        left = mid + 1;             // Try larger value
      }
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/