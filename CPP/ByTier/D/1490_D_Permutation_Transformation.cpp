// Problem: CF 1490 D - Permutation Transformation
// https://codeforces.com/contest/1490/problem/D

/*
 * Problem: D. Permutation Transformation
 * Purpose: Given a permutation, build a binary tree where each node's value is the maximum element in its subarray,
 *          and recursively build left and right subtrees from elements to the left and right of the maximum.
 *          Output the depth of each element in the constructed tree.
 *
 * Algorithms/Techniques:
 *   - Recursive tree construction based on max element in subarray
 *   - Preorder traversal to assign depths
 *
 * Time Complexity: O(n^2) in worst case (for a sorted array), but average is closer to O(n log n)
 * Space Complexity: O(n) for storing the tree and recursion stack
 */
#include <cstdio>
#include <vector>
void f(long start, long end, long curDepth, const std::vector<long> &dv,
       std::vector<long> &depth) {
  if (start >= end) { // Base case: no elements in this subarray
    return;
  }
  long idx(start); // Find the index of maximum element in current subarray
  for (long p = start + 1; p < end; p++) {
    if (dv[p] > dv[idx]) {
      idx = p;
    }
  }
  depth[idx] = curDepth; // Assign the depth to the maximum element
  f(start, idx, curDepth + 1, dv, depth);     // Recursively build left subtree
  f(idx + 1, end, curDepth + 1, dv, depth);   // Recursively build right subtree
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> t(n, 0);
    f(0, n, 0, a, t);
    for (long p = 0; p < n; p++) {
      printf("%ld ", t[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/