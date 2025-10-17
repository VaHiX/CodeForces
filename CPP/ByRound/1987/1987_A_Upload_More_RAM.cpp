// Problem: CF 1987 A - Upload More RAM
// https://codeforces.com/contest/1987/problem/A

/*
 * Problem: Upload More RAM
 * Algorithm: Greedy + Mathematical Observation
 * 
 * Purpose:
 *   Given n GBs of RAM to upload and a constraint that in any k consecutive seconds,
 *   at most 1 GB can be uploaded, find the minimum number of seconds needed.
 * 
 * Key Insight:
 *   To minimize time, we should maximize the amount uploaded per second, constrained
 *   by the k-window rule. The optimal strategy is to upload 1 GB every k seconds.
 *   
 *   If n = 1, we need exactly 1 second.
 *   For n > 1, we can use the formula: (n - 1) * k + 1
 *   This works because:
 *     - We upload 1 GB in the first second.
 *     - Then, for each remaining (n-1) GBs, we must wait k seconds before uploading next,
 *       hence adding k seconds per unit.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", (n - 1) * k + 1); // Key formula to compute minimum seconds
  }
}


// https://github.com/VaHiX/codeForces/