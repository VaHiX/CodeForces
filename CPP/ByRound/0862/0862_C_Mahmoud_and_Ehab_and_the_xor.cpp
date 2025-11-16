// Problem: CF 862 C - Mahmoud and Ehab and the xor
// https://codeforces.com/contest/862/problem/C

#include <cstdio>
// Purpose: Generate a set of n distinct non-negative integers whose XOR sum is exactly x.
// Algorithm: 
//   - If n == 1, just output x.
//   - If n == 2, output 0 and x (unless x is 0, in which case impossible).
//   - If n >= 3:
//     - For the first n-3 elements, use 0, 1, 2, ..., (n-4).
//     - Compute the XOR of these numbers and store in x.
//     - Then add three numbers such that their XOR with the previously computed x results in the desired x.
//     - The three numbers used are: u^x, v, u^v where u and v are large powers of 2.
// Time Complexity: O(n) - linear in the number of elements.
// Space Complexity: O(1) - constant extra space.
int main() {
  long n, x;
  scanf("%ld %ld", &n, &x);
  if (n == 1) {
    puts("YES");
    printf("%ld", x);
  } else if (n == 2) {
    if (x > 0) {
      puts("YES");
      printf("0 %ld\n", x);
    } else {
      puts("NO");
    }
  } else {
    puts("YES");
    long u(1L << 18), v(1L << 19); // Use large powers of 2 to ensure distinct elements
    for (long p = 0; p < n - 3; p++) {
      printf("%ld ", p);
      x ^= p; // Accumulate XOR of the initial elements
    }
    printf("%ld %ld %ld", u ^ x, v, u ^ v); // Add three carefully chosen elements
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/