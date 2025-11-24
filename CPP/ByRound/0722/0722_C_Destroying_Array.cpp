// Problem: CF 722 C - Destroying Array
// https://codeforces.com/contest/722/problem/C

/*
 * Problem: Destroying Array
 * 
 * Purpose: 
 *   Given an array of non-negative integers and a permutation of indices indicating the order 
 *   in which elements are destroyed, we need to compute the maximum sum of a contiguous 
 *   subarray (segment) that contains no destroyed elements after each destruction step.
 * 
 * Approach:
 *   - Process destructions in reverse order (from last to first).
 *   - Use a Union-Find (Disjoint Set Union) data structure to track connected components 
 *     of remaining elements.
 *   - For each element being "re-added" (in reverse order), we:
 *     * Mark it as present.
 *     * Merge it with its adjacent present elements (if any).
 *     * Keep track of the maximum sum of any connected component.
 *   - Store the result at each step and output in forward order.
 * 
 * Time Complexity: O(n * α(n)), where α(n) is the inverse Ackermann function (nearly constant).
 * Space Complexity: O(n)
 */

#include <stdint.h>
#include <cstdio>
#include <vector>

// Find root of set with path compression
int64_t find(int64_t x, std::vector<int64_t> &head) {
  return (head[x] == x) ? x : (head[x] = find(head[x], head)); // Path compression
}

int main() {
  int64_t n;
  scanf("%lld", &n);
  std::vector<int64_t> a(n);
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<int64_t> add(n);
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &add[p]);
    --add[p]; // Convert to 0-based indexing
  }
  std::vector<int64_t> head(n);
  for (int64_t p = 0; p < n; p++) {
    head[p] = p;
  }
  std::vector<int64_t> sz(n);
  for (int64_t p = 0; p < n; p++) {
    sz[p] = a[p]; // Initialize size (sum) of each element
  }
  std::vector<bool> present(n, 0); // Track if index is currently present
  std::vector<int64_t> cm(n, 0); // Store cumulative maximum sum at each step
  int64_t m(0); // Current maximum sum

  // Process in reverse order to simulate "adding back" elements
  for (int64_t p = n - 1; p >= 0; p--) {
    int64_t u = add[p]; // Index of element being "added back"
    present[u] = 1; // Mark element as present
    int64_t r = find(u, head); // Find root of the current component

    // If left neighbor is present, merge with it
    if (u > 0 && present[u - 1]) {
      int64_t s = find(u - 1, head);
      head[s] = r; // Link smaller root to larger root
      sz[r] += sz[s]; // Combine sums
    }

    // If right neighbor is present, merge with it
    if (u < n - 1 && present[u + 1]) {
      int64_t s = find(u + 1, head);
      head[s] = r;
      sz[r] += sz[s];
    }

    // Update global maximum
    m = (m > sz[r]) ? m : sz[r];
    cm[p] = m; // Store current maximum sum
  }

  // Output all results except the last one (which is always 0)
  for (int64_t p = 1; p < n; p++) {
    printf("%lld\n", cm[p]);
  }
  puts("0"); // Final output is always 0
  return 0;
}


// https://github.com/VaHiX/CodeForces/