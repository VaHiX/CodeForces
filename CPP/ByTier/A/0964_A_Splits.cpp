// Problem: CF 964 A - Splits
// https://codeforces.com/contest/964/problem/A

/*
Code Purpose:
This program calculates the number of different weights of splits for a given integer n.
A split is a nonincreasing sequence of positive integers that sum to n.
The weight of a split is the count of elements equal to the first element in the split.
The solution leverages the mathematical observation that the number of possible weights
is equal to 1 + floor(n / 2). This is derived from the fact that for any n, we can form
splits with weights 1, 2, ..., n/2, and n (when the entire number is a single element).

Algorithms/Techniques:
- Mathematical observation and formula derivation
- Direct computation without iteration

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <cstdio>

int main() {
  long n; // Read the input number n
  scanf("%ld", &n);
  printf("%ld\n", 1 + n / 2); // Output the number of possible weights using the derived formula
  return 0;
}


// https://github.com/VaHiX/CodeForces/