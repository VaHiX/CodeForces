// Problem: CF 1296 A - Array with Odd Sum
// https://codeforces.com/contest/1296/problem/A

/*
 * Problem: A. Array with Odd Sum
 * Purpose: Determine if it's possible to make the sum of an array odd by replacing elements.
 * Algorithm:
 *   - For each test case, count the number of odd elements in the array.
 *   - If there's at least one odd number and not all numbers are odd,
 *     we can make the sum odd by making all even numbers equal to one odd number.
 *   - The key insight: we can only make an odd sum if:
 *     1. There exists at least one odd element (cnt > 0), AND
 *     2. Not all elements are odd (cnt < n).
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0); // count of odd numbers
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += (x % 2); // increment if x is odd
    }
    // Check condition: at least one odd and not all odd => valid to make odd sum
    puts(((cnt & 1) || (1 <= cnt && cnt < n)) ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/