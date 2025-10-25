// Problem: CF 1562 A - The Miracle and the Sleeper
// https://codeforces.com/contest/1562/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long res = (r >= 2 * l) ? (r - 1) / 2 : (r - l); // Key logic: if r is at least 2*l, we can achieve (r-1)/2; otherwise, the maximum remainder is r-l
    printf("%ld\n", res);
  }
}
/*
 * Problem: Find the largest possible value of a mod b for integers a,b such that l <= b <= a <= r
 * Algorithm: Analytical approach based on properties of modulo operation and constraints
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

// https://github.com/VaHiX/codeForces/