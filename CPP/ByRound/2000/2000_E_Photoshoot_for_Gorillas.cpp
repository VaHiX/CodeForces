// Problem: CF 2000 E - Photoshoot for Gorillas
// https://codeforces.com/contest/2000/problem/E

/*
E. Photoshoot for Gorillas
Algorithms/Techniques: Greedy, Sorting, Prefix Sum, Grid Analysis
Time Complexity: O(n * m + w * log(w))
Space Complexity: O(n * m + w)

Problem:
Given a grid of dimensions n x m and k x k sub-squares, place w gorillas with given heights into the grid such that each cell holds at most one gorilla.
The spectacle value is the sum of all k x k sub-square values.
Goal: Maximize the total spectacle.

Approach:
1. Sort gorilla heights in descending order to use greedy strategy (place largest heights first).
2. For each cell in grid, calculate its "contribution" to the final spectacle by finding the minimum distance to any edge and to the center of a k x k square.
3. Sort all contributions in ascending order.
4. Multiply the largest gorilla heights with the largest contribution values.

Key Idea: 
- The contribution of a cell is determined by how many k x k sub-squares it can be part of, which depends on how close it is to the edges and center of the grid.
- To get maximum spectacle, we greedily pair large gorillas with large contributions.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
ll t, a[200005], s[200005];

int main() {
  cin >> t;
  while (t--) {
    ll n, m, k, w;
    cin >> n >> m >> k >> w;
    
    // Read gorilla heights
    for (int i = 1; i <= w; i++) {
      scanf("%lld", a + i);
    }
    
    // Sort gorillas in descending order so we can greedily assign largest to best positions
    sort(a + 1, a + 1 + w);
    
    // Precompute contribution values for each position in the grid
    // Contribution of position (i,j) is based on how close it is to edges
    // and how many k x k sub-squares it contributes to
    for (ll i = 1; i <= n; i++)
      for (ll j = 1; j <= m; j++)
        s[(i - 1) * m + j] = min(min(i, n - i + 1), min(k, n - k + 1)) *
                             min(min(j, m - j + 1), min(k, m - k + 1));
    
    // Sort the contribution values in ascending order
    sort(s + 1, s + 1 + n * m);
    
    // Greedily multiply largest gorillas with largest contributions
    long long ans = 0;
    for (int i = 0; i < w; i++) {
      ans += a[w - i] * s[n * m - i];
    }
    
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/