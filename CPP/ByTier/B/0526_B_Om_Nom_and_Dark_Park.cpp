// Problem: CF 526 B - Om Nom and Dark Park
// https://codeforces.com/contest/526/problem/B

/*
B. Om Nom and Dark Park

This problem involves a full binary tree of depth n, where each edge has an initial number of lights,
and we want to make all paths from root to leaves have the same total light count by adding minimum lights.

The algorithm works as follows:
1. Compute the total number of edges in the tree (2^(n+1) - 2).
2. Read the initial light values for each edge.
3. Process the tree from bottom up (leaves to root), computing the difference between max and min
   of two nodes at same level, and propagating the max value up to parent edges.
4. Sum all differences accumulated during processing.

Time Complexity: O(2^n) due to processing each level of the binary tree
Space Complexity: O(2^n) for storing the light values in a vector

Algorithms/Techniques:
- Binary Tree Traversal (bottom-up)
- Greedy approach using max difference computation
- Level-wise processing with propagation
*/

#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d\n", &n);
  long numEdges(0);
  long depthNodes(1);
  for (int p = 0; p < n; p++) {
    depthNodes *= 2; // Calculate number of nodes at each level
    numEdges += depthNodes; // Accumulate total edges
  }
  std::vector<long> lights(numEdges); // Initialize vector with total edges
  for (long p = 0; p < numEdges; p++) {
    scanf("%ld\n", &lights[p]); // Read initial light values
  }
  long total(0);
  while (depthNodes > 1) { // Process from leaves to root
    long initialSize = lights.size(); // Store current size
    for (int p = 0; p < depthNodes / 2; p++) {
      long a = lights.back();
      lights.pop_back(); // Pop last element
      long b = lights.back();
      lights.pop_back(); // Pop second last element
      long M = (a < b) ? b : a; // Max of two values
      long m = (a < b) ? a : b; // Min of two values
      total += (M - m); // Accumulate difference
      if (depthNodes > 2) { // Propagate max value upward
        lights[initialSize - 1 - depthNodes - p] += M;
      }
    }
    depthNodes /= 2; // Move to next level up
  }
  printf("%ld\n", total); // Print result
  return 0;
}


// https://github.com/VaHiX/codeForces/