// Problem: CF 1779 B - MKnez's ConstructiveForces Task
// https://codeforces.com/contest/1779/problem/B

/*
 * Code Purpose:
 * This code solves the problem of constructing an array of length n such that:
 * 1. All elements are non-zero integers.
 * 2. For every pair of adjacent elements, their sum equals the sum of the entire array.
 *
 * Algorithm:
 * - For n = 3, it's impossible to satisfy the constraints (proof given in note).
 * - For n > 3:
 *   - If n is odd, construct an array alternating between two values with specific offsets.
 *   - If n is even, construct an array alternating between 1 and -1.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) additional space (not counting input/output)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 3) {
      puts("NO");
      continue;
    } else {
      puts("YES");
      if (n % 2) {
        // For odd n > 3, we use two values a and b such that a + b = sum of array.
        // The sum of whole array is a + b (since each adjacent pair sums to total).
        // We set a = n/2 - 1 and b = -n/2, so a + b = -1.
        // Then the array alternates between these two values.
        long a(n / 2 - 1), b(-n / 2);
        for (long p = 0; p < n; p++) {
          printf("%ld ", p % 2 ? b : a);  // Alternate between a and b
        }
      } else {
        // For even n, use 1 and -1 alternating.
        // This ensures that each adjacent pair sums to 0, which equals total sum.
        for (long p = 0; p < n; p++) {
          printf("%ld ", 1 - 2 * (p % 2));  // 1 if p is even, -1 if p is odd
        }
      }
      puts("");  // Print newline after the array
    }
  }
}


// https://github.com/VaHiX/CodeForces/