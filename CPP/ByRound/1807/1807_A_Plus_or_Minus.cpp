// Problem: CF 1807 A - Plus or Minus
// https://codeforces.com/contest/1807/problem/A

#include <cstdio>
/*
 * Problem: Plus or Minus
 * Algorithm: Simple comparison of two possible equations a+b=c and a-b=c
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only using constant extra space
 *
 * Given three integers a, b, c, exactly one of the equations a+b=c or a-b=c is true.
 * Output '+' if a+b=c, otherwise output '-'.
 */
int main() {
  long t;  // Read number of test cases
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;  // Read the three integers for current test case
    scanf("%ld %ld %ld", &a, &b, &c);
    puts((a + b == c) ? "+" : "-");  // Check if a+b equals c, output accordingly
  }
}

// https://github.com/VaHiX/codeForces/