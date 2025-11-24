// Problem: CF 1886 A - Sum of Three
// https://codeforces.com/contest/1886/problem/A

/*
 * Problem: Sum of Three
 * 
 * Purpose: To find three distinct positive integers x, y, z such that:
 *          - x + y + z = n
 *          - None of x, y, z is divisible by 3
 * 
 * Algorithm:
 * - If n % 3 == 0:
 *   - If n < 12, no valid triplet exists (minimum sum is 1+2+3=6, but we need to avoid multiples of 3)
 *   - Otherwise, we can use: 1, 4, (n - 5) (since 1%3 != 0, 4%3 != 0, and (n-5)%3 != 0)
 * - If n % 3 != 0:
 *   - If n < 7, no valid triplet exists (minimum sum with 1,2,3 = 6, and 6%3 == 0; so we use 1,2,(n-3))
 *   - Otherwise, we can use: 1, 2, (n - 3) (since 1%3 != 0, 2%3 != 0, and (n-3)%3 != 0)
 * 
 * Time Complexity: O(t), where t is number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 3 == 0) {
      // If n is divisible by 3, we check if n is large enough to form a valid triplet.
      if (n < 12) {
        puts("NO");
      } else {
        // Use 1, 4, (n - 5) - all are not divisible by 3 and sum to n
        printf("YES\n1 4 %ld\n", n - 5);
      }
    } else {
      // If n is NOT divisible by 3, we check if n is large enough.
      if (n < 7) {
        puts("NO");
      } else {
        // Use 1, 2, (n - 3) - all are not divisible by 3 and sum to n
        printf("YES\n1 2 %ld\n", n - 3);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/