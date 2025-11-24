// Problem: CF 1352 B - Same Parity Summands
// https://codeforces.com/contest/1352/problem/B

/*
Purpose: This code solves the problem of representing a given number `n` as the sum of `k` positive integers that all have the same parity (either all odd or all even).

Approach:
- If n and k have the same parity (both odd or both even), we can use k-1 ones and one large number (n - (k - 1)) to satisfy the condition.
- If n is even and n >= 2*k, we can use k-1 twos and one large number (n - 2*(k - 1)) to satisfy the condition.
- Otherwise, it's impossible to represent n as sum of k same-parity positive integers.

Time Complexity: O(k) per test case due to printing k integers.
Space Complexity: O(1) - only using a constant amount of extra space.

Algorithms/Techniques: Greedy approach, parity checking, mathematical construction.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if ((n % 2 == k % 2) && (n >= k)) {
      // If n and k have the same parity and n is at least k, we can construct all 1s and one large number
      puts("YES");
      for (long p = 1; p < k; p++) {
        printf("1 ");  // print k-1 ones
      }
      printf("%ld\n", n - k + 1);  // print the last number which makes the sum equal to n
    } else if ((n % 2 == 0) && (n >= 2 * k)) {
      // If n is even and n >= 2*k, we can use k-1 twos and one large number
      puts("YES");
      for (long p = 1; p < k; p++) {
        printf("2 ");  // print k-1 twos
      }
      printf("%ld\n", n - 2 * k + 2);  // print the last number which makes the sum equal to n
    } else {
      // If none of the above conditions hold, no valid representation exists
      puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/