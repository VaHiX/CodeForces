// Problem: CF 1326 A - Bad Ugly Numbers
// https://codeforces.com/contest/1326/problem/A

/*
 * Problem: Bad Ugly Numbers
 * 
 * Task: Given a positive integer n, find any n-digit number s such that:
 *   1. s > 0
 *   2. s consists of exactly n digits
 *   3. No digit in s equals 0
 *   4. s is not divisible by any of its digits
 * 
 * Algorithm:
 * - For n = 1: return -1 (since any 1-digit number is divisible by itself)
 * - For n > 1: 
 *   - Start with "2" (a digit that is not divisible by 3, and 3 is not divisible by 2)
 *   - Append (n-1) instances of "3"
 *   - This ensures that:
 *     - Number is not divisible by any of its digits (since 2 is not divisible by 3, and 3 is not divisible by 2)
 *     - No digit is zero
 *     - The number is valid and satisfies all conditions
 * 
 * Time Complexity: O(n) per test case, due to the loop constructing the string of length n.
 * Space Complexity: O(n) for storing the result string.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n <= 1) {
      puts("-1");  // For n=1, such number is impossible (any 1-digit num is divisible by itself)
    } else {
      printf("2");  // Start with 2 to avoid divisibility issues
      for (long p = 1; p < n; p++) {
        printf("3");  // Append 3s for the rest of the digits
      };
      puts("");  // Print newline after constructing the number
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/