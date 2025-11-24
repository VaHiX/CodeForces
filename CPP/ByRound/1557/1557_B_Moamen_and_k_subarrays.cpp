// Problem: CF 1557 B - Moamen and k-subarrays
// https://codeforces.com/contest/1557/problem/B

/*
 * Problem: Moamen and k-subarrays
 * 
 * Algorithm/Technique: 
 *   - We need to determine if an array can be sorted by splitting it into exactly k subarrays,
 *     reordering them, and then merging.
 *   - Key insight: After sorting the array, we check how many "segments" (or "blocks") 
 *     of consecutive indices exist in the original array.
 *   - The number of such segments must be <= k for the solution to exist.
 *   - This is because each segment represents a contiguous part that cannot be moved 
 *     across others without violating the sorting property when reordering.
 *   
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array elements with their indices
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::pair<long, long>> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);  // Read the value
      v[p].second = p;            // Store the original index
    }
    sort(v.begin(), v.end());     // Sort by value, keeping track of original indices
    
    long cnt(1);  // Start with 1 segment (at least one)
    for (long p = 1; p < n; p++) {
      // If the current element's original index is NOT the next index after the previous one,
      // then we have a new segment
      cnt += (v[p].second != 1 + v[p - 1].second);
    }
    
    // If number of segments is <= k, sorting is possible
    puts(cnt <= k ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/