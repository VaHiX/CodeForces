// Problem: CF 1399 C - Boats Competition
// https://codeforces.com/contest/1399/problem/C

/*
C. Boats Competition
Purpose: Given n participants with weights, find the maximum number of teams (pairs) that can be formed such that all teams have the same total weight.

Algorithm:
- For each possible team total weight s (from 0 to 2*n), count how many pairs can be made.
- For each s, iterate through all possible first elements p in [1, n] such that p <= s - p (to avoid double counting).
- If p == s - p: use w[p]/2 pairs (since we pair elements with themselves)
- Else: use min(w[p], w[s-p]) pairs (since each element can only be used once)

Time Complexity: O(n^2) per test case, since we check all possible sums (up to 2*n) and for each sum iterate through at most n elements.
Space Complexity: O(n), for the vector w storing counts of weights.

Techniques:
- Frequency counting
- Two-pointer-like approach with enumeration of possible sums
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> w(n + 1, 0); // Vector to store frequency of each weight
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++w[x]; // Increment the count of weight x
    }
    long mx(0); // Variable to store maximum number of teams
    for (long sum = 0; sum <= 2 * n; sum++) { // Try all possible team weights
      long cnt(0);
      for (long p = 1; p <= n; p++) {
        if (p > sum - p) {
          continue; // Avoid double counting by skipping cases where p > sum-p
        } else if (sum - p > n) {
          continue; // Skip if complement weight exceeds maximum possible weight
        } else if (2 * p == sum) {
          cnt += w[p] / 2; // If p pairs with itself, divide count by 2
        } else {
          cnt += (w[p] < w[sum - p]) ? w[p] : w[sum - p]; // Take minimum of pair counts
        }
      }
      mx = (mx > cnt) ? mx : cnt; // Update maximum teams count
    }
    printf("%ld\n", mx);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/