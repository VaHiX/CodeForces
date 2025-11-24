// Problem: CF 731 C - Socks
// https://codeforces.com/contest/731/problem/C

/*
 * Problem: C. Socks
 * 
 * Algorithm/Techniques: Union-Find (Disjoint Set Union) + Frequency Counting
 * 
 * Time Complexity: O(n * α(n) + m + n * k), where α(n) is the inverse Ackermann function,
 *                  which is effectively constant for all practical purposes.
 * Space Complexity: O(n + k), for storing the union-find structure and color frequencies.
 * 
 * The problem involves grouping socks that must be the same color based on the days they are worn,
 * and then determining the minimum number of repaints needed to make all socks in each group
 * the same color, by choosing the most frequent color in each group.
 */

#include <cstdio>
#include <map>
#include <vector>

// Find function with path compression for Union-Find
long find(long x, std::vector<long> &v) {
  return (x == v[x]) ? x : (v[x] = find(v[x], v)); // Path compression optimization
}

int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<long> col(n, 0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &col[p]);
  }
  std::vector<long> head(n, 0);
  for (long p = 0; p < n; p++) {
    head[p] = p; // Initialize each element to be its own parent
  }
  
  // Process each day's instruction to union the socks that must be the same color
  while (m--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    long a = find(x, head);
    long b = find(y, head);
    head[b] = a; // Union the two sets
  }
  
  // Group socks by their root in the Union-Find structure
  std::vector<std::vector<long>> tp(n);
  for (long p = 0; p < n; p++) {
    tp[find(p, head)].push_back(col[p]); // Push color of sock p to the group it belongs to
  }
  
  long total(0);
  // For each group, find the minimum number of changes needed
  for (long p = 0; p < n; p++) {
    std::vector<long> v = tp[p];
    if (v.size() <= 0) {
      continue;
    }
    
    std::map<long, long> g; // Frequency map for colors in the current group
    long M(0); // Maximum frequency of a color in this group

    for (long q = 0; q < v.size(); q++) {
      long u = v[q];
      if (g.count(u) > 0) {
        ++g[u];
      } else {
        g[u] = 1;
      }
      M = (M > g[u]) ? M : g[u]; // Update maximum frequency
    }
    
    // Total changes = size of group - max frequency of a color in that group
    total += (v.size() - M);
  }
  
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/