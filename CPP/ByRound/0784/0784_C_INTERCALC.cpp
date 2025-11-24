// Problem: CF 784 C - INTERCALC
// https://codeforces.com/contest/784/problem/C

/*
Algorithm: Find maximum value in array and perform XOR with the last element
Techniques: Single pass iteration, bitwise XOR operation

Time Complexity: O(n) - Single loop through n elements
Space Complexity: O(1) - Only using constant extra space (variables max, x, p)

This program finds the maximum element in the given array and then computes
the XOR of this maximum value with the last element of the array.
*/
#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  int max(0), x(0);
  for (int p = 0; p < n; p++) {
    scanf("%d", &x);
    max = (x > max) ? x : max;  // Update max if current element is larger
  }
  printf("%d\n", (max ^ x));  // Output XOR of maximum and last element
  return 0;
}


// https://github.com/VaHiX/CodeForces/