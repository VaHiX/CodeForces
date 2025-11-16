// Problem: CF 2156 E - Best Time to Buy and Sell Stock
// https://codeforces.com/contest/2156/problem/E

/*
 * Purpose: Solve the "Best Time to Buy and Sell Stock" problem in a turn-based game.
 *          Players (Hao and Alex) alternately remove and lock elements from an array.
 *          Hao wants to minimize the beauty of the final locked array, Alex wants to maximize it.
 *          Beauty is defined as the maximum difference b_j - b_i where i < j in the final array.
 *
 * Algorithm: Binary search on the answer combined with a greedy construction and graph matching logic.
 * Time Complexity: O(n log(MaxVal - MinVal)) where MaxVal, MinVal are the range of values.
 * Space Complexity: O(n) for storing the graph and auxiliary arrays.
 *
 * Techniques:
 *   - Binary search over the possible beauty values.
 *   - Graph construction to model valid pairs of elements that could contribute to the beauty.
 *   - Greedy selection of candidates for maintaining a minimal/maximal difference.
 */

#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
int T, n, v[100010], mn[3];  // v: input array, mn: indices of smallest values so far
vector<int> e[100010];       // e[i]: list of indices connected to i based on the condition

// Function to check if a given beauty value 'x' is achievable
bool chk(int x) {
  int cs = 0;
  // Reset min array
  for (int i = 0; i < 3; i++)
    mn[i] = 0;
  // Clear edge list
  for (int i = 1; i <= n; i++)
    e[i].clear();
  
  // Process each element in the array
  for (int i = 1; i <= n; i++) {
    // For each of the top 3 smallest elements seen so far,
    // if current element minus that element >= x, connect them in graph
    for (int k = 0; k < 3; k++)
      if (v[i] - v[mn[k]] >= x)
        e[i].push_back(mn[k]), e[mn[k]].push_back(i);
    
    // Update the min array with current element (greedy maintenance of top 3)
    for (int k = 0, p = i; k < 3; k++)
      if (v[mn[k]] > v[p])
        swap(mn[k], p);
  }

  // Count how many nodes are connected to at least 2 other nodes
  for (int i = 1; i <= n; i++)
    if (e[i].size() >= 2)
      cs++;

  // Verify if a valid solution exists with at least 'cs' nodes forming valid edges
  for (int i = 1, f = 0; i <= n; i++, f = 0) {
    if (e[i].size() >= 2)
      f++;
    
    // Check if this node contributes to a valid group
    for (int p : e[i])
      if (e[p].size() == 2)
        f++;
    
    if (f == cs)
      return true;
  }
  return false;
}

int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d", &n), v[0] = 2e9 + 10;
    int res = 0;
    
    // Read input array
    for (int i = 1; i <= n; i++)
      scanf("%d", &v[i]);

    // Binary search over beauty values
    for (int l = -1e9, r = 1e9, m; l <= r;) {
      if (chk(m = (l + r) / 2))
        r = m - 1;   // Try smaller values
      else
        res = m, l = m + 1;   // Accept this value, try higher
    }
    printf("%d\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/