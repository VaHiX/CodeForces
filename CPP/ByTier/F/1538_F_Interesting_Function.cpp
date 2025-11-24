// Problem: CF 1538 F - Interesting Function
// https://codeforces.com/contest/1538/problem/F

/*
 * Problem: F. Interesting Function
 * 
 * Purpose: Calculate the total number of changed digits when incrementing from l to r,
 *          where each increment changes a suffix of digits.
 * 
 * Algorithm: 
 *   - For each digit position from right to left (from units to higher digits),
 *     we calculate how many times that position changes across the increments.
 *   - We simulate this by processing digits from right to left, keeping track of 
 *     how many numbers need to be incremented (r - l) at each level.
 *   - When a digit overflows (e.g., 9 -> 10), we carry the increment to the next
 *     higher digit, which is handled by dividing by 10.
 * 
 * Time Complexity: O(log r) per test case (since we process each digit level)
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long cnt(0);
    while (r) {
      // Add the number of operations at this digit level
      cnt += (r - l);
      // Move to the next higher digit
      r /= 10;
      l /= 10;
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/CodeForces/