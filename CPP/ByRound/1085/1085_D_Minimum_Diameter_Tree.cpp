// Problem: CF 1085 D - Minimum Diameter Tree
// https://codeforces.com/contest/1085/problem/D

/*
 * Problem: Minimum Diameter Tree
 * 
 * Algorithm: 
 * - This solution computes the minimum possible diameter of a tree 
 *   when edge weights are assigned such that their sum equals a given value s.
 * - The key idea is to distribute the total weight evenly among the "leaf-like" 
 *   structures of the tree, where leaf-like means nodes with degree > 1 that 
 *   are part of a path.
 * - The approach counts how many such "effective" edges exist, and then 
 *   distributes the weight accordingly.
 * 
 * Time Complexity: O(n), where n is the number of nodes. We traverse the tree twice:
 *                  once to count degrees, and once to process.
 * Space Complexity: O(n), for storing the degree of each node.
 */

#include <stdio.h>
int n, l, g[100001], i, a, b;
double x;
int main() {
  // Read number of nodes and total weight
  scanf("%d%lf", &n, &x);
  
  // Read edges and count degree of each node
  for (i = 1; i < n; i++)
    scanf("%d%d", &a, &b), g[a]++, g[b]++;
  
  // Count how many nodes have degree 1 (i.e. leaves)
  // These are the "endpoints" of paths in the tree
  for (i = 1; i <= n; i++)
    l += !(g[i] - 1); // increment if degree equals 1
  
  // Distribute the total weight (2*x) among the effective paths (number of leaves)
  // This gives the minimal possible diameter
  x = (2 * x) / l;
  
  // Print result with 15 decimal places
  printf("%.15lf", x);
}


// https://github.com/VaHiX/CodeForces/