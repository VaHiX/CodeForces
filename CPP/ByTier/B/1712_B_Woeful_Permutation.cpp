// Problem: CF 1712 B - Woeful Permutation
// https://codeforces.com/contest/1712/problem/B

/*
B. Woeful Permutation
Problem: Find a permutation of length n such that the sum of LCM(1,p_1) + LCM(2,p_2) + ... + LCM(n,p_n) is maximized.

Algorithm:
- For odd n: Place 1 at the start, then pair up remaining numbers (2,3), (4,5), etc., with each pair in reversed order
- For even n: Pair up all numbers (1,2), (3,4), ..., (n-1,n) in reversed order

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (not counting input/output)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) { // If n is odd
      printf("1 "); // Place 1 at the beginning
      for (long p = 2; p < n; p += 2) { // Process pairs from 2 to n-1
        printf("%ld %ld ", p + 1, p); // Print pair in reversed order
      }
    } else { // If n is even
      for (long p = 1; p < n; p += 2) { // Process pairs from 1 to n-1
        printf("%ld %ld ", p + 1, p); // Print pair in reversed order
      }
    }
    puts(""); // Print newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/