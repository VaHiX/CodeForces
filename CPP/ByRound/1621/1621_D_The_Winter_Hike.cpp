// Problem: CF 1621 D - The Winter Hike
// https://codeforces.com/contest/1621/problem/D

/*
Code Purpose:
This solution computes the minimum cost to move all friends from the top-left n×n grid 
to the bottom-right n×n grid in a 2n×2n grid, where some cells are covered with snow. 
The friends can move through row/column operations, but if they step on snow, they become ill. 
Snow can be removed at a cost, and the goal is to minimize total cost.

Algorithms/Techniques:
- Greedy approach: Identify minimal cost paths for friends to reach the destination.
- Key insight: Friends from the top-left quadrant (1..n, 1..n) must reach bottom-right quadrant (n+1..2n, n+1..2n).
- The key idea is that the minimum cost to reach each cell in the destination quadrant is the cost of removing snow from that cell.
- Additionally, we must consider that some friends will have to traverse from specific starting edges of the grid:
  - Top edge of the source grid (row 1) to bottom edge of destination grid (row 2n)
  - Left edge of the source grid (col 1) to right edge of destination grid (col 2n)
- For this, we evaluate the minimal cost among specific edge cells.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

The algorithm uses a simple greedy approach where:
1. The cost of all destination cells (bottom-right n×n quadrant) is added to the answer.
2. Then we calculate the minimal cost among the edge cells that could be used for routing friends from source to destination.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int c[511][511], t, n;
long long ans;
int main() {
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d", &n);
    for (int i = 1; i <= n * 2; i++)
      for (int j = 1; j <= n * 2; j++)
        scanf("%d", &c[i][j]);
    ans = 0;
    // Add cost for all cells in the bottom-right quadrant (destination area)
    for (int i = n + 1; i <= n * 2; i++)
      for (int j = n + 1; j <= n * 2; j++)
        ans += c[i][j];
    // Add the minimum cost among specific edge cells to allow routing
    ans += min({c[1][n + 1], c[1][n * 2], c[n][n + 1], c[n][n * 2], c[n + 1][1],
                c[n + 1][n], c[n * 2][1], c[n * 2][n]});
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/