// Problem: CF 981 C - Useful Decomposition
// https://codeforces.com/contest/981/problem/C

#include <cstdio>
#include <vector>
/*
Algorithm: 
- The problem asks to decompose a tree into simple paths such that:
  1. Each edge belongs to exactly one path
  2. Any two paths share at least one common vertex
- Key insights:
  - If a tree has a node with degree > 2, it must be the center of all paths.
  - If a tree has more than one node with degree > 2, no valid decomposition exists.
  - If there are no nodes with degree > 2, then all leaves can be connected into a single path.
  - Otherwise, if there's one node with degree > 2 (the center), connect each leaf to this center.

Time Complexity: O(n) - we iterate through edges and nodes once.
Space Complexity: O(n) - for adjacency list representation of the tree.
*/
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> g(n + 1); // adjacency list
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  bool possible(true);
  long center(-1); // Node with degree > 2
  std::vector<long> ends; // Leaves (degree 1)
  for (long p = 1; p <= n; p++) {
    if (g[p].size() == 1) {
      ends.push_back(p); // Collect leaves
    } else if (g[p].size() > 2) {
      if (center >= 0) {
        possible = false; // Multiple centers => impossible
        break;
      } else {
        center = p; // Found the center
      }
    }
  }
  if (!possible) {
    puts("No");
    return 0;
  } else {
    puts("Yes");
    if (center < 0 && ends.size() >= 2) {
      // No center, but at least 2 leaves - connect them directly
      printf("1\n%ld %ld\n", ends[0], ends[1]);
    } else {
      // Use the center to connect all leaves
      printf("%ld\n", ends.size());
      for (long p = 0; p < ends.size(); p++) {
        printf("%ld %ld\n", center, ends[p]);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/