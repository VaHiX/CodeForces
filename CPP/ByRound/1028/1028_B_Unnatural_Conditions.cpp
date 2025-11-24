// Problem: CF 1028 B - Unnatural Conditions
// https://codeforces.com/contest/1028/problem/B

/*
 * Code Purpose:
 *   Given two integers n and m, find two positive integers a and b such that:
 *   - s(a) >= n (sum of digits of a is at least n)
 *   - s(b) >= n (sum of digits of b is at least n)
 *   - s(a + b) <= m (sum of digits of a + b is at most m)
 *
 * Algorithm/Techniques:
 *   - Construct a and b by using a pattern of 9s and 0s to maximize digit sum
 *     with minimal impact on the sum of digits of their sum.
 *   - Use a = 999...9990999...999 (d-1 nine followed by a zero, then another 9)
 *   - Use b = 0999...9990999...999 (a zero followed by d-1 nine, then another 9)
 *   - This ensures each number has digit sum approximately 9*d, and their sum
 *     is close to 1000...000 (a 1 followed by d zeros), so sum of digits is 1.
 *   - Adjust construction to meet the requirement s(a + b) <= m, which is always satisfied
 *     because the construction uses 9s in a way that makes a + b have a small digit sum.
 *
 * Time Complexity:
 *   O(d) where d = (n + 8) / 9, which is O(1) since n is bounded by 1129.
 *
 * Space Complexity:
 *   O(d) for storing the output strings, which is O(1) since d is bounded.
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  long d = (n + 8) / 9;  // Calculate number of digit groups needed to get at least n digit sum
  printf("9");  // First digit of a is 9
  for (long p = 1; p < d; p++) {
    printf("09");  // Append "09" for the rest of a's digits
  }
  puts("");  // Print newline for a
  for (long p = 1; p < d; p++) {
    printf("90");  // Append "90" for the rest of b's digits
  };
  puts("91");  // Last part of b is "91"
  return 0;
}


// https://github.com/VaHiX/CodeForces/