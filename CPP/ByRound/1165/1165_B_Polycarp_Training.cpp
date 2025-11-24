// Problem: CF 1165 B - Polycarp Training
// https://codeforces.com/contest/1165/problem/B

/*
B. Polycarp Training
Algorithm: Greedy approach with sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for the vector storage

The problem asks to find the maximum number of consecutive days Polycarp can train,
where on day k, he must solve exactly k problems. He can only choose from contests
he hasn't used yet, and each contest provides exactly a_i problems (he uses k of them).

Approach:
1. Sort the contests in ascending order to apply greedy strategy.
2. For each day k (starting from 1), check if there's a contest with at least k problems.
3. If so, use that contest and increment the day count.
4. Continue until no such contest exists.

This greedy approach works because we want to minimize the waste of problems
from larger contests — using smaller contests first allows us to keep larger ones
for later days when more problems are required.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read the number of problems in each contest
  }
  sort(a.begin(), a.end()); // Sort contests by number of problems (ascending)
  long cur(0); // Track current day number (1-indexed)
  for (long p = 0; p < n; p++) {
    if (a[p] >= cur + 1) { // If this contest has enough problems for the current day
      ++cur; // Increment day counter
    }
  }
  printf("%ld\n", cur); // Print maximum number of training days
  return 0;
}


// https://github.com/VaHiX/codeForces/