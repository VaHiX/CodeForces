// Problem: CF 1758 B - XOR = Average
// https://codeforces.com/contest/1758/problem/B

/*
Code Purpose:
This program finds a sequence of n integers such that the bitwise XOR of all elements equals the average of the elements.
The solution uses a constructive approach:
- If n is odd, all elements are set to 1.
- If n is even, the first two elements are 1 and 3, and the rest are 2.
This ensures that the XOR and average are equal due to the mathematical properties of these numbers.

Algorithms/Techniques:
- Constructive algorithm
- Bitwise XOR properties
- Mathematical reasoning on averages and XORs

Time Complexity: O(n) per test case, as we iterate through the sequence once.
Space Complexity: O(1) excluding input/output storage.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) {
      // If n is odd, use all 1s
      for (long p = 0; p < n; p++) {
        printf("1 ");
      }
    } else {
      // If n is even, use 1, 3, and then 2s
      printf("1 3 ");
      for (long p = 2; p < n; p++) {
        printf("2 ");
      }
    }
    puts(""); // Print newline after each sequence
  }
}


// https://github.com/VaHiX/CodeForces/