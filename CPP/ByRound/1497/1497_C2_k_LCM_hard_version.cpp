// Problem: CF 1497 C2 - k-LCM (hard version)
// https://codeforces.com/contest/1497/problem/C2

/*
Algorithm/Technique: Greedy approach with special handling of remaining sum.
The idea is to use as many 1's as possible to reduce the problem to a smaller sum,
then handle the remaining sum (n-k+1) in a way that keeps LCM small.

Time Complexity: O(1) per test case (constant time operations)
Space Complexity: O(1) (only using a constant amount of extra space)

The algorithm works by:
1. Placing (k-3) ones at the start, reducing n to n-(k-3).
2. Then dealing with the remaining sum n' = n-(k-3) using:
   - If n' is odd, split as 1 + n'/2 + n'/2.
   - If n' is even and divisible by 4, split as n'/4 + n'/4 + n'/2.
   - Otherwise, split as 2 + (n'-2)/2 + (n'-2)/2.
This ensures the LCM remains bounded by n/2.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    for (long p = 3; p < k; p++) {
      printf("1 ");
      --n;
    }
    // After placing k-3 ones, we have n remaining to split into 3 numbers
    if (n % 2) {
      // If n is odd, split as 1 + n/2 + n/2
      printf("1 %ld %ld\n", n / 2, n / 2);
    } else if (n % 4 == 0) {
      // If n is divisible by 4, split as n/4 + n/4 + n/2
      printf("%ld %ld %ld\n", n / 4, n / 4, n / 2);
    } else {
      // Otherwise split as 2 + (n-2)/2 + (n-2)/2
      printf("2 %ld %ld\n", n / 2 - 1, n / 2 - 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/