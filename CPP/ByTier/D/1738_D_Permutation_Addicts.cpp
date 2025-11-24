// Problem: CF 1738 D - Permutation Addicts
// https://codeforces.com/contest/1738/problem/D

/*
Code Purpose:
This code reconstructs a permutation 'a' and a threshold 'k' from a given sequence 'b'.
The algorithm utilizes the relationships defined in the problem to deduce the permutation and threshold.

Algorithms/Techniques:
- Graph traversal using adjacency lists (represented via vector<int> e[])
- Greedy reconstruction based on the order of elements in 'b'
- Dynamic assignment of element values based on indices and values in the 'b' array

Time Complexity: O(n^2) in the worst case due to nested loops when traversing the graph structure.
Space Complexity: O(n) for storing the permutation and auxiliary data structures.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5 + 2;
int T, n, k, b[N];
vector<int> e[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), k = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", b + i);
      k = max(k, min(b[i], i)); // Determine threshold k based on min of b[i] and i
      e[b[i]].push_back(i); // Build adjacency list using b[i] as key
    }
    printf("%d\n", k);
    for (int x = e[0].size() ? 0 : n + 1, y;;) { // Initialize x based on presence of 0 in e
      y = 0;
      for (int i : e[x]) // Traverse adjacency list
        if (e[i].size()) // If i has outgoing edges
          y = i; // Update y to next node
        else // If no outgoing edge, print the current node
          printf("%d ", i);
      if (!y) // If no next node, break
        break;
      printf("%d ", y);
      x = y; // Move to next node
    }
    printf("\n");
    for (int i = 0; i <= n + 1; ++i) // Clear the adjacency list
      e[i].clear();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/