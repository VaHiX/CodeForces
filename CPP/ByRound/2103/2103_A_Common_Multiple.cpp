// Problem: CF 2103 A - Common Multiple
// https://codeforces.com/contest/2103/problem/A

/*
 * Problem: Maximum Size of Beautiful Subsequence
 * 
 * Algorithm: Greedy approach with tracking unique elements.
 * 
 * For each test case:
 *   - Iterate through the array and maintain a boolean array `v` to track seen values.
 *   - For each element `x`, if it's not seen before, increment the counter (`total`) and mark it as seen.
 *   - This ensures that we count only unique elements in the subsequence, which is necessary for the "distinct" requirement in the beautiful array definition.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) (fixed-size boolean array of size 101)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool v[101] = {0};   // Tracks which numbers have been seen
    long total(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      total += 1 - v[x];   // If x is not seen before, add 1 to total and mark as seen
      v[x] = 1;
    }
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/