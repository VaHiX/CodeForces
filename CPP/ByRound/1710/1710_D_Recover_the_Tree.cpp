// Problem: CF 1710 D - Recover the Tree
// https://codeforces.com/contest/1710/problem/D

/*
Code Purpose:
This code recovers a tree structure from given segment connectivity information.
Each segment [l,r] is labeled as good (connected) or bad (not connected).
The algorithm iterates over all possible segment lengths and uses a greedy
approach to identify edges in the tree based on the connectivity of segments.

Algorithms/Techniques:
- Greedy approach to reconstructing tree edges
- Segment-based connectivity checking
- Union-find like logic to merge components

Time Complexity:
O(n^3) - Three nested loops: segment length, start position, and internal
processing Space Complexity: O(n^2) - For storing the segment information in 2D
array s

*/

#include <stdio.h>

const int o = 2010;
int T, n, l[o],
    r[o];     // l and r arrays track left and right boundaries of components
char s[o][o]; // s[i][j] stores if segment [i,j] is good (1) or bad (0)
int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d", &n);
    // Initialize l and r arrays to each vertex being its own component
    for (int i = 1; i <= n; ++i)
      l[i] = r[i] = i, scanf("%s", s[i] + i);
    // Iterate over all possible segment lengths from 2 to n
    for (int len = 2; len <= n; ++len)
      for (int i = 1, j; i <= n - len + 1; ++i)
        // Check if the segment [i, i+len-1] is good and l[i] != l[j]
        // (components differ)
        if (s[i][j = i + len - 1] > 48 && l[i] - l[j]) {
          // Add an edge between i and j
          printf("%d %d\n", i, j);
          int t[2] = {
              i,
              j}; // t[0] and t[1] represent the endpoints of the current edge
          // Connect vertices in the middle of segments to the current edge
          // endpoints
          for (int k = i + 1, cur = 1; k < l[j]; ++k)
            if (l[k] == k) // If k is the root of its component
              printf("%d %d\n", t[cur], k),
                  t[cur] = k, cur ^= 1; // Alternate between t[0] and t[1]
          // Merge segments by updating l and r arrays
          for (int L = l[i], R = r[j], k = L; k <= R; ++k)
            l[k] = L, r[k] = R;
        }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/