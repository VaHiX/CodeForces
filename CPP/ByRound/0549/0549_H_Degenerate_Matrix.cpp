// Problem: CF 549 H - Degenerate Matrix
// https://codeforces.com/contest/549/problem/H

/*
Purpose: This code finds the minimum possible norm ||A - B|| where B is a degenerate matrix (determinant = 0) 
         and A is a given 2x2 matrix. The solution uses the fact that the minimum norm to a degenerate matrix
         is related to the determinant and the maximum of certain linear combinations of matrix elements.

Algorithms/Techniques:
- Use of determinant calculation for 2x2 matrix
- Maximal absolute value of linear combinations of elements to find optimal perturbation
- Mathematical optimization to compute minimal distance to the set of degenerate matrices

Time Complexity: O(1) - constant time operations only
Space Complexity: O(1) - only a few integer and floating-point variables used
*/

#include <bits/std_abs.h>
#include <stdint.h>
#include <cstdio>
#include <algorithm>

int main() {
  int64_t a, b, c, d;
  scanf("%lld %lld %lld %lld\n", &a, &b, &c, &d);
  int64_t det = std::abs(a * d - b * c);  // Calculate determinant of matrix A
  double k =
      std::max(std::max(std::abs(a + b + c + d), std::abs(a - b + c - d)),  // Compute max of four linear combinations
               std::max(std::abs(a - b - c + d), std::abs(a + b - c - d)));
  printf("%.9f\n", k ? det / k : 0.0);  // Output the result, handling case when k is zero
  return 0;
}


// https://github.com/VaHiX/CodeForces/