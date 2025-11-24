// Problem: CF 1833 C - Vlad Building Beautiful Array
// https://codeforces.com/contest/1833/problem/C

/*
C. Vlad Building Beautiful Array
Purpose:
This code determines whether it's possible to construct a "beautiful array" b from a given array a.
A beautiful array has all elements of the same parity (all even or all odd) and all elements are positive.

Algorithms/Techniques:
- For each test case, we analyze the input array to check conditions that allow building a beautiful array.
- Key insight is that if there exists at least one odd number in the input array,
  then it's always possible to create a beautiful array where all elements are odd.
- Otherwise (all numbers even), we must verify if we can generate an odd number via operations.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7);        // Initialize minimum value to a large number
    bool evens(true);        // Flag to track if all numbers are even
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      mn = (mn < x) ? mn : x;  // Track the smallest number in array
      if (x % 2) {             // If current number is odd
        evens = false;         // Set flag to false since not all numbers are even
      }
    }
    puts((mn % 2 || evens) ? "YES" : "NO");  // Output result based on conditions
  }
}


// https://github.com/VaHiX/codeForces/