// Problem: CF 1767 B - Block Towers
// https://codeforces.com/contest/1767/problem/B

/*
B. Block Towers

Algorithm:
This problem involves redistributing blocks among towers to maximize the number of blocks on tower 1.
The key insight is that we can only move blocks from a tower with more blocks to a tower with fewer blocks.
We process the towers in increasing order of their block counts and simulate the moves optimally.

Approach:
1. For each tower (except the first), if its block count is greater than current x (which represents the maximum we can have on tower 1),
   we calculate how many blocks we can add to tower 1 using the formula: (a[p] + x + 1) / 2.
   This ensures that we move blocks efficiently and maintain optimal distribution.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the vector of block counts
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    std::vector<long> a(n - 1); // Store block counts of towers 2 to n
    for (long p = 0; p + 1 < n; p++) {
      scanf("%ld", &a[p]); // Read block counts of towers 2 through n
    }
    sort(a.begin(), a.end()); // Sort to process from smallest to largest
    for (long p = 0; p + 1 < n; p++) {
      if (a[p] <= x) {
        continue; // Skip if current tower's count is not greater than x
      }
      x = (a[p] + x + 1) / 2; // Calculate new maximum value for tower 1
    }
    printf("%ld\n", x); // Output the final result for tower 1
  }
}


// https://github.com/VaHiX/codeForces/