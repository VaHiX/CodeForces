// Problem: CF 1426 C - Increase and Copy
// https://codeforces.com/contest/1426/problem/C

/*
C. Increase and Copy
Problem: Minimum moves to make array sum at least n.
Operations:
  1. Increase any element by 1.
  2. Append a copy of any element to the end.

Approach: 
  - Use mathematical insight: optimal strategy involves building an array with 
    roughly equal elements (to minimize increases), then appending them efficiently.
  - For a given target sum n, find minimal steps to reach it using the formula:
    Let s = floor(sqrt(n)), try configurations of size around s + R where R is 
    a small offset to balance increases and copies.
    
Time Complexity: O(1) per test case (constant number of iterations)
Space Complexity: O(1) (only uses fixed number of variables)
*/
#include <cmath>
#include <cstdio>
int main() {
  const long R = 10; // Offset for checking nearby values around sqrt(n)
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s = std::sqrt(n); // Estimate of square root of n
    long lb = (s >= R + 1) ? (s - R) : 1; // Lower bound for iteration loop
    long ub = s + R; // Upper bound for iteration loop
    long res(n + 1); // Initialize result to large value
    
    // Check values in range [lb, ub] to find minimum operations needed
    for (long p = lb; p <= ub; p++) {
      long test = (p - 1) + (n + p - 1) / p - 1; 
      // This evaluates a candidate solution:
      // (p-1): number of increases needed to build array of size p  
      // (n + p - 1) / p: minimum copies required to achieve sum >= n
      // Subtract 1 because we're counting starting from 1-indexed elements
      res = (res < test) ? res : test;
    }
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/