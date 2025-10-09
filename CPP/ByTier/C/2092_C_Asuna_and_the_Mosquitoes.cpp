// Problem: CF 2092 C - Asuna and the Mosquitoes
// https://codeforces.com/contest/2092/problem/C

/*
C. Asuna and the Mosquitoes
Purpose:
  This code solves a problem where Asuna wants to maximize the beauty of her tower gifts by redistributing heights through operations that transfer 1 from an odd-numbered tower to an even-numbered tower (when possible). The key idea is that operations can only be done between towers with different parity (odd/even), and we aim to increase the maximum height after all valid operations.

Algorithm:
  - For each test case, count how many odd and even numbers in the input.
  - If both odd and even numbers exist, we can effectively transfer values to make one tower very large while keeping others small; so answer is sum of all elements minus number of odd elements plus 1 (as a special adjustment).
  - Otherwise, no beneficial operations are possible — return the maximum element.

Time Complexity:
  O(n) per test case, where n is the number of towers.
Space Complexity:
  O(1), constant space usage.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cd(0), cv(0), mx(0); // cd: count of odd numbers, cv: count of even numbers, mx: max element
    long long s(0); // sum of all elements
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cd += (x % 2);      // increment odd counter if x is odd
      cv += (1 - x % 2);  // increment even counter if x is even
      mx = (mx > x ? mx : x); // keep track of maximum element
      s += x;             // accumulate sum
    }
    // If both odd and even numbers exist, we can perform operations to get maximum
    // such that result equals total sum minus number of odds plus 1.
    // Otherwise, no beneficial transfers are possible; return max value.
    printf("%lld\n", (cd && cv) ? (s - cd + 1) : mx);
  }
}


// https://github.com/VaHiX/codeForces/