// Problem: CF 1437 D - Minimal Height Tree
// https://codeforces.com/contest/1437/problem/D

/*
D. Minimal Height Tree
Algorithms/Techniques: BFS traversal analysis, dynamic programming on tree structure

Time Complexity: O(n) per test case
Space Complexity: O(n) for the auxiliary arrays

Problem Description:
Given a BFS traversal order of a tree rooted at vertex 1, find the minimum possible height
of such a tree. The children of each node are visited in ascending order.

The solution uses a dynamic programming approach to compute the height of each node
in the BFS sequence, considering how far back we need to look to determine parent-child
relationships and maintain minimum height.
*/

#include <cstdio>
#include <vector>
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
    std::vector<long> h(n, 0); // h[p] stores the height of node a[p]
    h[1] = 1; // Root's child has height 1
    long idx(0); // idx tracks the furthest ancestor with same or smaller height
    for (long p = 2; p < n; p++) {
      if (a[p] < a[p - 1]) { // If current node is less than previous, it's a sibling
        ++idx;
      }
      h[p] = h[idx] + 1; // Height is height of ancestor plus one
    }
    printf("%ld\n", h.back()); // Output height of last node in BFS order
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/