// Problem: CF 1339 A - Filling Diamonds
// https://codeforces.com/contest/1339/problem/A

/*
 * Problem: A. Filling Diamonds
 * Purpose: Calculate the number of ways to fully cover a belt-like area of 4n-2 triangles 
 *          using diamond shapes, where each diamond consists of two triangles.
 *          
 * Algorithm: The problem follows a pattern that can be solved mathematically.
 *            After analyzing the structure, it turns out the answer is simply n.
 *            This is because for a belt-like area with 4n-2 triangles,
 *            there are exactly n distinct ways to tile it using the given diamond shapes.
 *          
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of memory regardless of input size
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);  // Read number of test cases
  while (t--) {
    long n;
    scanf("%ld", &n);  // Read the value of n for current test case
    printf("%ld\n", n);  // Output the result, which is simply n
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/