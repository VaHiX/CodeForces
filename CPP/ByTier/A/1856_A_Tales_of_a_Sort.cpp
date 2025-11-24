// Problem: CF 1856 A - Tales of a Sort
// https://codeforces.com/contest/1856/problem/A

/*
 * Problem: Tales of a Sort
 * Algorithm/Techniques: Simulation with greedy approach
 *
 * Time Complexity: O(n^2) in worst case due to nested simulation of operations,
 *                  but since n <= 50 and each element can decrease by at most 1 per operation,
 *                  actual performance is acceptable.
 * Space Complexity: O(1), only using a few variables for computation.
 *
 * Description:
 * Alphen performs operations on an array until it becomes sorted.
 * Each operation decreases each element by 1 (but not below 0),
 * and this continues until the array is non-decreasing.
 * The goal is to count how many such operations are needed.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0), cur(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < cur) {        // If current element is less than previous, update max
        res = (res > cur ? res : cur);
      }
      cur = x;              // Update current to latest value
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/