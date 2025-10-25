// Problem: CF 1802 A - Likes
// https://codeforces.com/contest/1802/problem/A

/*
 * Problem: Nikita's contribution changed quickly due to likes and unlikes.
 *          Given a shuffled sequence of events (positive = like, negative = unlike),
 *          we need to compute the maximum and minimum possible number of likes at each second.
 *
 * Algorithm:
 *   - For each test case:
 *     - Count positive (likes) and negative (unlikes) numbers
 *     - Compute maximum likes: for each second i, accumulate all positive values up to that point
 *     - Compute minimum likes: simulate the earliest possible unlikes to minimize final count
 *
 * Time Complexity: O(n) per test case where n is the length of input array
 * Space Complexity: O(1) additional space (excluding input/output)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pos(0), neg(0); // Count of positive and negative numbers
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      pos += (x > 0);  // Increment pos if x is positive (like)
      neg += (x < 0);  // Increment neg if x is negative (unlike)
    }
    // First line: maximum number of likes at each second
    for (long p = 1; p <= n; p++) {
      printf("%ld ", p <= pos ? p : (2 * pos - p));  // Compute the max possible at time p
    }
    puts("");
    
    // Second line: minimum number of likes at each second
    for (long p = 1; p <= n; p++) {
      printf("%ld ", (p <= 2 * neg) ? (p % 2) : (p - 2 * neg));  // Compute the min possible at time p
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/