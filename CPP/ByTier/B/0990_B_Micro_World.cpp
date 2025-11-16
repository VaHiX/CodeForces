// Problem: CF 990 B - Micro-World
// https://codeforces.com/contest/990/problem/B

/*
Algorithm: Greedy + Two Pointers
Approach:
- Sort the array of bacteria sizes.
- Use a greedy strategy to minimize the number of remaining bacteria.
- For each bacterium, try to swallow as many smaller bacteria as possible within the limit K.
- Use two pointers to efficiently determine which bacteria can be swallowed.

Time Complexity: O(n log n) due to sorting, where n is the number of bacteria.
Space Complexity: O(n) for the vector b used to mark which bacteria remain.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort bacteria sizes
  std::vector<long> b(n, 1);  // Initialize all bacteria as remaining (1)
  long ind(0);  // Pointer to track the current bacteria being considered for swallowing
  for (long p = 0; p < n; p++) {
    // While we can swallow bacteria with index 'ind' into current bacterium 'p'
    while (a[ind] < a[p] && a[p] <= a[ind] + k) {
      b[ind] = 0;  // Mark the smaller bacterium as swallowed
      ++ind;
    }
    // Skip bacteria that are too small to be considered (beyond K range)
    while (a[ind] + k < a[p]) {
      ++ind;
    }
  }
  long cnt(0);
  for (long p = 0; p < n; p++) {
    cnt += b[p];  // Count remaining bacteria
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/