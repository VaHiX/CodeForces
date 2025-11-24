// Problem: CF 1000 B - Light It Up
// https://codeforces.com/contest/1000/problem/B

/* 
B. Light It Up
Algorithms/Techniques: Greedy, Prefix/Suffix Analysis

Time Complexity: O(n)
Space Complexity: O(n)

The problem involves finding the optimal way to insert one element into a given sequence of switch times,
to maximize the total time the lamp is lit. The solution uses a reverse iteration approach:
- We simulate the process from the end towards the beginning.
- At each step, we track two values: 'orig' (time when the lamp was originally on) and 'off' (time during which the lamp would be off if we added an element at that position).
- The key insight is to find the maximum difference between 'off - orig' to determine where adding a new switch will help.
- Finally, we compute the result as original lit time plus the best gain possible from one insertion.

This approach ensures optimal performance with linear time and space complexity, due to single pass through array and vector storage.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n + 2, 0); // Vector to store program with padding at start and end
  a[n + 1] = m; // Last element is the moment when power turns off
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]); // Read initial program values
  }
  long orig(0), off(0), mx(0); // orig: total on-time, off: potential off time, mx: max gain from insertion
  for (long p = n; p >= 0; p--) {
    if (p % 2) { // If odd index, it means we're processing a "turn off" event in reverse
      off += a[p + 1] - a[p]; // Accumulate off time
    } else { // If even index, processing "turn on" event in reverse
      orig += a[p + 1] - a[p]; // Accumulate on time
    }
    mx = (mx > off - orig) ? mx : (off - orig); // Keep track of the maximum difference found so far
  }
  printf("%ld\n", orig + (mx > 0) * (mx - 1)); // Output result with potential gain from one insertion
  return 0;
}


// https://github.com/VaHiX/codeForces/