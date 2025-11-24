// Problem: CF 2033 E - Sakurako, Kosuke, and the Permutation
// https://codeforces.com/contest/2033/problem/E

/*
E. Sakurako, Kosuke, and the Permutation
Algorithms/Techniques: Cycle Detection in Permutations
Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)

The problem asks to make a permutation "simple" by swapping elements,
where a simple permutation has each element either at its correct position
or points to its correct position (i.e., p[i] = i or p[p[i]] = i).

This can be viewed as finding cycles in the permutation graph.
Each cycle of length k requires (k-1)/2 swaps to resolve.
We use DFS to detect cycles and count minimal swaps needed.
*/

#include <stdio.h>
#include <iosfwd>

#define ll long long
using namespace std;
int n, t, a[1000001];
bool b[1000001];

// DFS to find cycle length starting from node x
int dfs(int x) {
  if (b[x]) // If already visited, we've completed a cycle
    return 0;
  b[x] = 1; // Mark current node as visited
  return dfs(a[x]) + 1; // Continue the cycle
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]); // Read the permutation
    
    int ans = 0;
    for (int i = 1; i <= n; i++)
      if (!b[a[i]]) // Only process unvisited nodes
        ans += (dfs(a[i]) - 1) / 2; // Count swaps needed for this cycle
    
    // Reset visited array after processing each test case
    for (int i = 1; i <= n; i++)
      b[a[i]] = 0;
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/