// Problem: CF 914 A - Perfect Squares
// https://codeforces.com/contest/914/problem/A

/*
 * Problem: Find the largest number in an array that is not a perfect square.
 *
 * Algorithms/Techniques:
 * - Iterate through each element in the array.
 * - For each element:
 *   - If the number is non-negative, check if it's a perfect square by computing
 *     the integer square root and checking if square of that root equals the number.
 *   - If it is not a perfect square and greater than current answer, update answer.
 *   - If the number is negative, it can't be a perfect square, so compare directly.
 *
 * Time Complexity: O(n * log(max_value)) where n is the length of the array.
 *   - For each number, we do a sqrt operation which takes O(log(max_value)).
 *   - We iterate through the array once => O(n * log(max_value)).
 *
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 */

#include <cmath>
#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long ans(-1e8);  // Initialize to a very small value
  while (n--) {
    long x;
    scanf("%ld", &x);
    if (x >= 0) {
      long s = sqrt(x);  // Compute integer square root
      // Check if x is NOT a perfect square (s^2 < x)
      if ((s * s < x) && (x > ans)) {
        ans = x;
      }
    } else {
      // Negative numbers can't be perfect squares, compare directly
      ans = (ans > x) ? ans : x;
    }
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/