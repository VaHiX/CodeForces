// Problem: CF 1862 C - Flower City Fence
// https://codeforces.com/contest/1862/problem/C

/*
C. Flower City Fence
Algorithm: The solution checks if a given non-increasing sequence of plank heights forms a symmetric fence when laid horizontally.
Technique: Difference array method is used to simulate the horizontal layout and verify symmetry.

Time Complexity: O(n) per test case, where n is the number of planks.
Space Complexity: O(n) for the difference array 'w'.

The idea is to:
1. Use a difference array to represent how many planks are "active" at each height level.
2. For each plank of height h, increment the start (0) and decrement after height h.
3. Compute prefix sums to get actual counts of active planks at each level.
4. If this matches the original sequence, then it's symmetric.

This is similar to checking if a histogram can be mirrored along its base.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n); // Read the input fence heights
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    std::vector<long> w(n + 1); // Difference array for tracking active planks
    bool res(true); // Flag to store whether the result is valid
    
    // Process each plank and update difference array
    for (long p = 0; res && p < n; p++) {
      ++w[0];                          // Increment start of interval
      if (v[p] > n) {                  // If height exceeds number of planks, impossible to be symmetric
        res = false;
      } else {
        --w[v[p]];                     // Decrement end+1 of interval
      }
    }
    
    long cs(0); // Running prefix sum for difference array
    
    // Compute prefix sums and check if they match original sequence
    for (long p = 0; res && p < n; p++) {
      cs += w[p];                      // Add current difference to running sum
      if (cs != v[p]) {                // If prefix sum doesn't match plank height, not symmetric
        res = false;
      }
    }
    
    puts(res ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/