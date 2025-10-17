// Problem: CF 1754 B - Kevin and Permutation
// https://codeforces.com/contest/1754/problem/B

/*
B. Kevin and Permutation
Purpose: Arrange numbers 1 to n such that the minimum absolute difference between consecutive elements is maximized.
Algorithm: 
    - For even n: pair numbers as (n/2, n), (n/2-1, n-1), ..., (1, n/2+1) and place them in order
    - For odd n: same pattern, but last number n is appended at the end
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding input/output)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Start from n/2 and go down to 1, pairing with numbers from n/2+1 to n
    for (long p = n / 2; p > 0; p--) {
      printf("%ld %ld ", p, p + (n / 2)); // Print pair: p and p + n/2
    }
    // If n is odd, print the last number n at the end
    if (n % 2) {
      printf("%ld", n);
    }
    puts(""); // New line after each test case
  }
}


// https://github.com/VaHiX/codeForces/