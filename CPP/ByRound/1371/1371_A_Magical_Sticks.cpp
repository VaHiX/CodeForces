// Problem: CF 1371 A - Magical Sticks
// https://codeforces.com/contest/1371/problem/A

/*
Problem: Magical Sticks
Purpose: Given n sticks of lengths 1 to n, determine the maximum number of sticks of equal length that can be formed by connecting sticks.
Algorithm: 
    - For each n, the maximum number of equal-length sticks is (n + 1) / 2.
    - This works because we can pair sticks optimally to form as many same-length sticks as possible.
Time Complexity: O(1) per test case
Space Complexity: O(1)

Input: Multiple test cases, each with a single integer n (1 <= n <= 10^9)
Output: Maximum number of sticks of equal length possible
*/
#include <cstdio>
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n; // Current input value
    scanf("%ld", &n);
    printf("%ld\n", (n + 1) / 2); // Optimal result formula
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/