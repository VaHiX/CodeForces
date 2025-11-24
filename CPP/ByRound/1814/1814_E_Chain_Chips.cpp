// Problem: CF 1814 E - Chain Chips
// https://codeforces.com/contest/1814/problem/E

/*
 * Problem: Chain Chips
 * 
 * Purpose: 
 *   This code computes the minimum cost to rearrange chips on a chain graph such that 
 *   no chip ends up on a vertex with its own index. It uses a segment tree with dynamic 
 *   programming to efficiently update and query the minimum cost after edge weight changes.
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming on a Segment Tree
 *   - Lazy Propagation (implicit in this code through update and build functions)
 *   - Tree-based DP with 2D states
 * 
 * Time Complexity:
 *   - Building the segment tree: O(n)
 *   - Each update and query: O(log n)
 *   - Total for q queries: O(q * log n)
 * 
 * Space Complexity:
 *   - O(n) for the segment tree storage and auxiliary arrays
 * 
 * State Representation:
 *   dp[rt][i][j] represents the maximum profit of assigning chips to vertices
 *   where the root corresponds to a segment of the chain.
 *   i indicates if the leftmost vertex is assigned.
 *   j indicates if the rightmost vertex is assigned.
 * 
 * The final result is derived as: 2 * (total_sum - max_profit)
 * where max_profit is the best DP value from the root.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
using ll = long long;
int a[200009]; // Array storing edge weights
ll dp[800009][2][2]; // Segment tree for DP states

// Function to recompute the DP values for a node based on its children
void refe(int rt) {
  int l = rt * 2;
  int r = rt * 2 + 1;
  // Compute the maximum profit for different assignment states
  dp[rt][0][0] = max({dp[l][0][0] + dp[r][0][0], dp[l][0][1] + dp[r][0][0],
                      dp[l][0][0] + dp[r][1][0]});
  dp[rt][1][0] = max({dp[l][1][0] + dp[r][0][0], dp[l][1][1] + dp[r][0][0],
                      dp[l][1][0] + dp[r][1][0]});
  dp[rt][0][1] = max({dp[l][0][0] + dp[r][0][1], dp[l][0][1] + dp[r][0][1],
                      dp[l][0][0] + dp[r][1][1]});
  dp[rt][1][1] = max({dp[l][1][0] + dp[r][0][1], dp[l][1][1] + dp[r][0][1],
                      dp[l][1][0] + dp[r][1][1]});
}

// Build the segment tree
void build(int rt, int l, int r) {
  if (l == r) {
    dp[rt][0][0] = 0;     // No assignment at both ends
    dp[rt][0][1] = -1e18; // Invalid state
    dp[rt][1][0] = -1e18; // Invalid state  
    dp[rt][1][1] = a[l];  // Assignment at both ends (cost = edge weight)
    return;
  }
  int mid = (l + r) / 2;
  build(rt * 2, l, mid);       // Build left subtree
  build(rt *2 + 1, mid + 1, r); // Build right subtree
  refe(rt); // Recompute current node from children
}

// Update the weight of an edge and propagate the change in the tree
void update(int rt, int l, int r, int x) {
  if (l == r) {
    dp[rt][0][0] = 0;
    dp[rt][0][1] = -1e18;
    dp[rt][1][0] = -1e18;
    dp[rt][1][1] = a[l];
    return;
  }
  int mid = (l + r) / 2;
  if (mid >= x)
    update(rt * 2, l, mid, x);      // Go left
  else
    update(rt * 2 + 1, mid + 1, r, x); // Go right
  refe(rt); // Recompute current node after change
}

int main() {
  ll sum = 0; // Total weight of all edges
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i]; // Calculate total initial weight
  }
  --n;
  build(1, 1, n); // Build the segment tree

  int q;
  scanf("%d", &q);
  while (q--) {
    int k, x;
    scanf("%d%d", &k, &x);
    sum -= a[k];   // Adjust total weight
    a[k] = x;      // Change the weight
    sum += a[k];   // Add new weight to total
    update(1, 1, n, k); // Update the segment tree
    // Final cost = 2 * (total - best assignment)
    printf("%lld\n", (sum - dp[1][0][0]) * 2);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/