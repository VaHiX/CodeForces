// Problem: CF 2078 A - Final Verdict
// https://codeforces.com/contest/2078/problem/A

/*
 * Problem: Determine if an array of integers can be reduced to a single value x
 *          through a sequence of operations where the array is split into k equal parts,
 *          and each part's average replaces that part in the array.
 *
 * Algorithm:
 *   - For each test case, check whether it's possible to reduce the array to [x].
 *   - Key insight: If we can achieve x as the final value, then at every step of the process,
 *     the average of the elements in a subsequence must equal x.
 *   - This is only possible if the sum of all elements in the original array equals n * x,
 *     since the final value is x and there are n total elements, so sum = n * x.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long sum(0);
    for (long p = 0; p < n; p++) {
      long x; // Local variable to read input
      scanf("%ld", &x);
      sum += x;
    }
    puts(sum == n * x ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/