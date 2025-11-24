// Problem: CF 939 A - Love Triangle
// https://codeforces.com/contest/939/problem/A

#include <cstdio>
#include <vector>
/*
 * Problem: Love Triangle
 * 
 * Description:
 * Given a list of n planes where each plane i likes plane f[i], determine if there exists a 
 * love triangle, i.e., a cycle of length 3 (A -> B -> C -> A).
 * 
 * Algorithm:
 * For each plane p, we follow the chain of liking: p -> f[p] -> f[f[p]] -> f[f[f[p]]].
 * If f[f[f[p]]] == p, then we have a triangle.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Direct simulation of the chain of relationships
 * - Early termination when a triangle is found
 */
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> f(n + 1);
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &f[p]);
  }
  bool triangle(false);
  for (long p = 1; p <= n && !triangle; p++) {
    // Check if f[f[f[p]]] points back to p, forming a triangle
    triangle = triangle | (f[f[f[p]]] == p);
  }
  puts(triangle ? "YES" : "NO");
  return 0;
}

// https://github.com/VaHiX/CodeForces/