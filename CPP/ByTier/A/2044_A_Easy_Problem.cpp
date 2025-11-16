// Problem: CF 2044 A - Easy Problem
// https://codeforces.com/contest/2044/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", n - 1);
  }
}
/*
Problem: Count ordered pairs of positive integers (a,b) such that a = n - b
Algorithm: Mathematical observation
- For equation a = n - b where both a and b are positive integers
- We need a > 0 and b > 0
- From a = n - b and a > 0: n - b > 0 → b < n
- From b > 0 and b < n: 0 < b < n
- Since b is a positive integer, b can take values 1, 2, ..., n-1
- So there are exactly (n-1) valid ordered pairs
Time Complexity: O(t) where t is number of test cases
Space Complexity: O(1)
*/

// https://github.com/VaHiX/codeForces/