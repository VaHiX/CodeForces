// Problem: CF 630 H - Benches
// https://codeforces.com/contest/630/problem/H

#include <stdint.h>
#include <iostream>

/*
Code Purpose:
This program calculates the number of ways to place 5 benches in a grid of n×n paths such that each bench is at an intersection and each path (both east-west and north-south) contains at most one bench. The solution uses combinatorial mathematics.

Algorithm:
1. Select 5 east-west paths from n paths: C(n,5) = n!/(5!(n-5)!)
2. Select 5 north-south paths from n paths: C(n,5) = n!/(5!(n-5)!)
3. Arrange the 5 benches on the selected 5×5 intersection grid: 5!

The total ways = C(n,5) × C(n,5) × 5!

Time Complexity: O(1) - The computation involves only a constant number of arithmetic operations.
Space Complexity: O(1) - Only a constant amount of memory is used.
*/

int main() {
  int64_t n;
  std::cin >> n;
  // Calculate C(n,5) * C(n,5) * 5!
  // C(n,5) = n*(n-1)*(n-2)*(n-3)*(n-4) / (5*4*3*2*1) = n*(n-1)*(n-2)*(n-3)*(n-4) / 120
  int64_t ans = n * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 120;
  ans *= n * (n - 1) * (n - 2) * (n - 3) * (n - 4); // Multiply by another C(n,5) and 5!
  std::cout << ans << std::endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/