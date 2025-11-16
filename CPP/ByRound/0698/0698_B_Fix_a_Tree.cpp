// Problem: CF 698 B - Fix a Tree
// https://codeforces.com/contest/698/problem/B

/*
 * Problem: Fix a Tree
 * 
 * Purpose: Given a sequence representing parent pointers of a tree,
 *          fix the minimum number of elements to make it a valid tree representation.
 * 
 * Approach:
 *   - Use Union-Find (Disjoint Set Union) to detect connected components.
 *   - Identify the root (a node pointing to itself).
 *   - If no root exists, assign one.
 *   - Ensure each component has exactly one representative (root) and fix pointers accordingly.
 * 
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (nearly constant)
 * Space Complexity: O(n) for the arrays and Union-Find structure
 */

#include <cstdio>
#include <vector>

// Find operation with path compression for Union-Find
long find(std::vector<long> &f, long x) {
  return (f[x] == x) ? x : (f[x] = find(f, f[x])); // Path compression
}

// Join operation to merge two sets in Union-Find
void join(std::vector<long> &f, long x, long y) { 
  f[y] = find(f, x); 
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1), f(n + 1); // a: input array, f: Union-Find parent array
  
  // Read input parent pointers
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  
  // Initialize Union-Find structure
  for (long p = 1; p <= n; p++) {
    f[p] = p;
  }
  
  long root(0);
  // Process each node to build Union-Find structure and identify root
  for (long p = 1; p <= n; p++) {
    if (a[p] == p) {
      root = p; // Found the root
    }
    join(f, a[p], p); // Connect node p with its parent
  }
  
  long count(0);
  // If no root was found, set one and increment change count
  if (root <= 0) {
    root = find(f, 1);
    a[root] = root;
    ++count;
  }
  
  // Fix remaining nodes to ensure they point to root of their component
  for (long p = 1; p <= n; p++) {
    if (find(f, p) != p || p == root) {
      continue; // Skip if already root or part of a component
    }
    ++count;
    a[p] = root; // Set parent of component root to global root
  }
  
  printf("%ld\n", count);
  for (long p = 1; p <= n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/