// Problem: CF 1992 A - Only Pluses
// https://codeforces.com/contest/1992/problem/A

/*
Problem: A. Only Pluses
Task: Maximize the product a*b*c by incrementing any of the three numbers at most 5 times.

Algorithms/Techniques: Greedy approach
Time Complexity: O(1) - The loop runs a fixed number of iterations (5), so time is constant.
Space Complexity: O(1) - Only a constant amount of extra space is used.

The strategy is to always increase the smallest of the three numbers to maximize the product.
This greedy choice guarantees the maximum result since increasing the smallest number
has the highest marginal gain in the product.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    for (long p = 0; p < 5; p++) {           // Perform at most 5 increments
      if (a <= b && a <= c) {                // If 'a' is the smallest
        ++a;                                 // Increment it
      } else if (b <= a && b <= c) {         // If 'b' is the smallest
        ++b;                                 // Increment it
      } else if (c <= a && c <= b) {         // If 'c' is the smallest
        ++c;                                 // Increment it
      }
    }
    printf("%ld\n", a * b * c);              // Print final product
  }
}


// https://github.com/VaHiX/codeForces/