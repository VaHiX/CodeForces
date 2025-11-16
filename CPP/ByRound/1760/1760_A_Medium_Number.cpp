// Problem: CF 1760 A - Medium Number
// https://codeforces.com/contest/1760/problem/A

/*
 * Problem: A. Medium Number
 * Purpose: Given three distinct integers a, b, and c, find the median (middle value) among them.
 * Algorithms/Techniques: Direct comparison of all possible orderings using if-statements.
 * Time Complexity: O(1) - constant time since there are exactly 6 comparisons and no loops.
 * Space Complexity: O(1) - only a fixed amount of variables used regardless of input size.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {     // Process each test case
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c); // Read three integers
    long res;
    if (a < b && b < c) {   // Case: a < b < c -> b is middle
      res = b;
    }
    if (a < c && c < b) {   // Case: a < c < b -> c is middle
      res = c;
    }
    if (b < a && a < c) {   // Case: b < a < c -> a is middle
      res = a;
    }
    if (b < c && c < a) {   // Case: b < c < a -> c is middle
      res = c;
    }
    if (c < a && a < b) {   // Case: c < a < b -> a is middle
      res = a;
    }
    if (c < b && b < a) {   // Case: c < b < a -> b is middle
      res = b;
    }
    printf("%ld\n", res);   // Output the result
  }
}


// https://github.com/VaHiX/codeForces/