// Problem: CF 1663 C - Pōja Verdon
// https://codeforces.com/contest/1663/problem/C

#include <cstdio>
/*
C. Pōja Verdon
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Aenar has an array $$$a$$$ consisting of $$$n$$$ integers.

Algorithm: Simple array summation
Time complexity: O(n) - single pass through the array
Space complexity: O(1) - only using constant extra space

The code reads an array of integers and computes their sum.
*/
int main() {
  long n;                    // Read the size of the array
  scanf("%ld", &n);
  long s(0);                 // Initialize sum to 0
  for (long p = 0; p < n; p++) {  // Loop through each element
    long x;                  // Temporary variable to store current element
    scanf("%ld", &x);        // Read the current element
    s += x;                  // Add current element to running sum
  }
  printf("%ld\n", s);        // Print the final sum
}

// https://github.com/VaHiX/codeForces/