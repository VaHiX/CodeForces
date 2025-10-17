// Problem: CF 1969 A - Two Friends
// https://codeforces.com/contest/1969/problem/A

/*
Problem: A. Two Friends
Algorithms/Techniques: Graph traversal (find cycles), greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

This problem models a directed graph where each node points to its best friend.
We need to find the minimum number of nodes to select such that at least 2 nodes
can "activate" others via the friendship chain. This is achieved by finding
the shortest cycle in the graph and selecting enough nodes to break all cycles
of length less than or equal to 2, minimizing the total invitations needed.

The approach:
1. Model the friendships as a directed graph.
2. Traverse each unvisited node to detect cycles using DFS-like traversal.
3. For each cycle detected, we must send at least as many invitations as 
   the size of the smallest cycle to ensure at least 2 friends come.
4. Return minimum such number found.

The code:
- Uses vector v to represent the graph with 1-based indexing
- Traverses nodes and marks visited by setting value to 0 during traversal
- Detects cycles by following p[i] -> p[p[i]] -> ... until a 0 is encountered
- Keeps track of minimum cycle length found, which gives the minimum invitations needed.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1); // 1-based indexing
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &v[p]);
    }
    long mncnt(3); // Initialize with 3 since we need at least 2 friends, so minimum is 2 invitations
    for (long p = 1; p <= n; p++) {
      if (!v[p]) { // Skip already visited nodes
        continue;
      }
      long x(p), cnt(0); // Start traversal from node p, count cycle length
      while (v[x]) { // While current node hasn't been processed yet
        ++cnt; // Increment cycle length counter
        long y = v[x]; // Get next node in chain
        v[x] = 0; // Mark current node as visited by setting to 0
        x = y; // Move to next node
      }
      mncnt = (cnt < mncnt ? cnt : mncnt); // Update minimum cycle length
    }
    printf("%ld\n", mncnt);
  }
}


// https://github.com/VaHiX/codeForces/