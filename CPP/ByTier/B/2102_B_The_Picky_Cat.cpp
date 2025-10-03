// Problem: CF 2102 B - The Picky Cat
// https://codeforces.com/contest/2102/problem/B

/*
 * Problem: B. The Picky Cat
 *
 * Algorithm: Greedy approach
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * The task is to determine if we can make the element at index 1 (a[0]) become the median
 * of the array after applying any number of sign flips (multiplying by -1).
 *
 * Key idea:
 * For a[0] to be the median, at least half of the other elements must be >= |a[0]| 
 * (when a[0] is positive) or <= |a[0]| (when a[0] is negative). We try both possibilities
 * by checking if flipping a[0] gives us a better chance.
 *
 * Approach:
 * - For each test case, we process elements from index 1 onward.
 * - We consider absolute values of all elements.
 * - Count how many of them are >= |a[0]| (the "better" candidates).
 * - If at least (n-1)/2 of the remaining elements satisfy this condition, output "YES", else "NO".
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    x = (x > 0 ? x : -x); // Take absolute value of first element
    long cnt(0);
    for (long p = 1; p < n; p++) {
      long y;
      scanf("%ld", &y);
      y = (y > 0 ? y : -y); // Take absolute value of current element
      cnt += (y >= x);      // Increment counter if absolute value is >= |a[0]|
    }
    puts(cnt >= (n - 1) / 2 ? "YES" : "NO"); // Check if enough elements meet condition
  }
}


// https://github.com/VaHiX/codeForces/