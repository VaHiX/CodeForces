// Problem: CF 2055 B - Crafting
// https://codeforces.com/contest/2055/problem/B

/*
B. Crafting
Algorithms/Techniques: Greedy, Mathematical Analysis

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves determining whether we can transform an initial array of materials 'a' into a target array 'b'
using a specific operation: selecting a material i and spending 1 unit of every other material to gain 1 unit of material i.
This operation preserves the total sum of all materials.

Key Insight:
- If we can perform operations, we are essentially redistributing materials while keeping the total sum constant.
- The necessary condition for a valid solution is that:
    1. All required amounts must be achievable, meaning that for each material i,
       there exists some sequence of moves such that final count >= b[i].
    2. The difference between current and desired counts (a[i] - b[i]) can be viewed as surplus or deficit.
    3. By analyzing the net change vector d[i] = a[i] - b[i], we can determine if it's possible to 
       redistribute such that all values in d are non-negative after applying operations.

Approach:
1. Compute difference array: d[i] = a[i] - b[i]
2. Analyze the negative values:
    - If any d[i] < 0, then material i is deficient.
    - Let diff be the minimum (most negative) value among all d[i].
    - For each material with d[i] < 0, its deficit must be made up from others.
3. Check if it's possible to use excess resources (d[i] > 0) such that after applying diff:
    - All d[i] + diff >= 0
This ensures redistribution is valid.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> dv(n); // Difference array: a[i] - b[i]
    for (long p = 0; p < n; p++) {
      scanf("%ld", &dv[p]);
    }
    bool ans(true);
    long diff(0); // Tracks the minimum deficit in the difference array
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      dv[p] -= x; // Update to difference: a[i] - b[i]
      if (dv[p] < 0) { // If current material is in deficit
        if (diff) { // If we already have another deficit
          ans = false; // Impossible if multiple deficits exist
        } else {
          diff = dv[p]; // Set the deficit amount
        }
      }
    }
    for (long p = 0; ans && p < n; p++) {
      if (dv[p] < 0) {
        continue; // Skip deficits, they need to be compensated by positive values
      }
      if (dv[p] + diff < 0) { // If adding deficit to surplus makes it negative, impossible
        ans = false;
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/