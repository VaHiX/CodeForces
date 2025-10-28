// Problem: CF 1351 A - A+B (Trial Problem)
// https://codeforces.com/contest/1351/problem/A

#include <cstdio>
/*
A. A+B (Trial Problem)
Algorithms/Techniques: Simple arithmetic addition with multiple test cases
Time complexity: O(t) where t is the number of test cases
Space complexity: O(1) - only using constant extra space

This program reads multiple pairs of integers and computes their sum.
For each test case, it reads two integers a and b, then prints their sum a+b.
*/
int main() {
  long t;                       // Read number of test cases
  scanf("%ld", &t);
  while (t--) {                 // Process each test case
    long a, b;                  // Declare variables for the two numbers
    scanf("%ld %ld", &a, &b);   // Read the two numbers
    printf("%ld\n", a + b);     // Print their sum
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/