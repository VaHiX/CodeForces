// Problem: CF 1368 A - C+=
// https://codeforces.com/contest/1368/problem/A

/*
 * Purpose: This program determines the minimum number of operations required to make 
 *          either variable 'a' or 'b' strictly greater than a given value 'n'.
 *          The operations allowed are "a += b" or "b += a", which add the value of one 
 *          variable to another.
 *
 * Algorithm:
 *   - Use a greedy approach: always add the smaller value to the larger one.
 *   - Continue until either 'a' or 'b' exceeds 'n'.
 *   - Count the number of operations performed.
 *
 * Time Complexity: O(log(max(a, b, n))) - Each step roughly doubles the smaller value,
 *                  so the number of iterations is logarithmic.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, n;
    scanf("%ld %ld %ld", &a, &b, &n);
    long cnt(0);
    while (a <= n && b <= n) {
      if (a < b) {
        a += b;   // Add smaller value to larger one
      } else {
        b += a;   // Add smaller value to larger one
      }
      ++cnt;      // Increment operation count
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/