// Problem: CF 605 B - Lazy Student
// https://codeforces.com/contest/605/problem/B

/*
 * Problem: Lazy Student
 * Purpose: Given edge weights and inclusion status in MST, construct a valid graph
 *          such that the given MST is correct.
 *
 * Algorithm:
 *   1. Sort edges by weight, with included edges (sp=1) prioritized over excluded (sp=0).
 *   2. Assign vertex IDs to each edge based on inclusion status.
 *   3. For included edges, link to a new vertex ID.
 *   4. For excluded edges, link to existing vertices in a way to avoid creating a smaller MST.
 *
 * Time Complexity: O(m log m) due to sorting.
 * Space Complexity: O(m) for storing edges and output.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

struct edge {
  long num, w, sp;
};

// Custom comparator for sorting edges:
// - Sort by weight ascending
// - For same weight, include edges (sp=1) come before exclude edges (sp=0)
bool edgeCompare(edge A, edge B) {
  if (A.w < B.w) {
    return true;
  } else if (A.w == B.w && A.sp > B.sp) {
    return true;
  }
  return false;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<edge> d(m);
  for (long p = 0; p < m; p++) {
    d[p].num = p;  // Store original index
    scanf("%ld %ld", &d[p].w, &d[p].sp);
  }
  
  // Sort edges using custom comparator
  sort(d.begin(), d.end(), edgeCompare);
  
  long cnt(0), cur(1), left(2), right(2);
  bool possible(true);
  std::vector<std::pair<long, long>> g(m, std::make_pair(1, 1));  // Initialize output edges
  
  for (long p = 0; p < m; p++) {
    if (d[p].sp) {
      // This edge is included in MST - connect to a new vertex
      g[d[p].num].second = ++cur;
    } else {
      // This edge is NOT included in MST
      ++left;
      if (left >= right) {
        // Need to move to next level of vertices
        if (right >= cur) {
          // Impossible to construct a valid graph
          possible = false;
          break;
        } else {
          left = 2;
          ++right;
        }
      }
      // Connect this excluded edge to existing vertices in a way such that it doesn't form a valid MST
      g[d[p].num].first = left;
      g[d[p].num].second = right;
    }
  }
  
  if (possible) {
    for (long p = 0; p < m; p++) {
      printf("%ld %ld\n", g[p].first, g[p].second);
    }
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/