// Problem: CF 1419 D2 - Sage's Birthday (hard version)
// https://codeforces.com/contest/1419/problem/D2

/*
D2. Sage's Birthday (hard version)
Purpose: Given a sequence of ice sphere prices, reorder them to maximize the number of "cheap" spheres.
         A sphere is cheap if it is strictly less than both neighbors.
         The goal is to maximize the count of such cheap spheres in the final arrangement.

Algorithms/Techniques:
- Sorting and greedy rearrangement
- Use of reverse iterators and pop_back for efficient manipulation
- Greedy assignment to place smaller values between larger ones to create more cheap points

Time Complexity: O(n log n) due to sorting step
Space Complexity: O(n) for storing the vectors a and b
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  if (n <= 1) {
    printf("0\n%ld\n", a[0]);
    return 0;
  }
  sort(a.rbegin(), a.rend()); // Sort in descending order to get largest elements first
  std::vector<long> b(n, -1); // Initialize result array with -1s (unfilled positions)
  for (long p = 1; p < n; p += 2) {
    b[p] = a.back(); // Place smallest remaining element at odd indices (to potentially be cheap)
    a.pop_back();
  }
  for (long p = 0; p < n; p++) {
    if (b[p] < 0) {
      b[p] = a.back(); // Fill remaining unfilled positions with remaining elements
      a.pop_back();
    }
  }
  long cnt(0);
  for (long p = 1; p + 1 < n; p++) {
    cnt += (b[p - 1] > b[p] && b[p] < b[p + 1]); // Count how many positions are cheap
  }
  printf("%ld\n", cnt);
  for (long p = 0; p < n; p++) {
    printf("%ld ", b[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/