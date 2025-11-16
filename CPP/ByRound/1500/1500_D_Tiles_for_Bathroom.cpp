// Problem: CF 1500 D - Tiles for Bathroom
// https://codeforces.com/contest/1500/problem/D

/*
Algorithm: 
This solution uses a dynamic programming approach with prefix sums to efficiently count valid subsquares.
For each cell (i, j), it keeps track of the minimum size of a subsquare ending at that cell that exceeds the color limit q.
It uses a technique similar to sliding window, where we build upon previously computed values.
Time Complexity: O(n^2 * q)
Space Complexity: O(n^2 * q)

The approach:
- For each cell (i, j), we compute the list of colors in the smallest subsquare ending at this cell.
- We use a technique similar to 2D prefix sums to quickly compute the number of distinct colors in any subsquare.
- We maintain a 'd' array where d[k] represents the number of k x k subsquares with at most q colors.
- For each cell, we update the count of valid subsquares of various sizes using the computed minimum size.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define pb push_back
#define fors(i, a, b) for (int i = (a); i < (b); ++i)
#define P pair<int, int>
using namespace std;
int a[1555][1555], vis[2500000], n, q, d[1555], cnt[1555][1555];
vector<P> col[1555][1555], t;

void sol(int x, int y) {
  // Add current cell to the list of potential subsquares
  t.pb(P(0, a[x][y]));
  
  // Merge from top cell if exists
  if (x > 1)
    for (P p : col[x - 1][y])
      t.pb(p);
  
  // Merge from left cell if exists
  if (y > 1)
    for (P p : col[x][y - 1])
      t.pb(p);
  
  // Merge from top-left cell if exists
  if (x > 1 && y > 1)
    for (P p : col[x - 1][y - 1])
      t.pb(p);
  
  // Sort the merged list to handle unique colors efficiently
  sort(t.begin(), t.end());
  
  // Count unique colors and update current grid (col[x][y])
  for (P p : t) {
    p.first++; // increment the size of the subsquare
    if (!vis[p.second]) // if color not yet seen in the current window
      vis[p.second] = 1, col[x][y].pb(p);
    if (col[x][y].size() > q) // if exceeds q colors, stop early
      break;
  }
  
  // Reset visited flags for next use
  for (P p : col[x][y])
    vis[p.second] = 0;
  t.clear();
}

int main() {
  cin >> n >> q;
  
  // Process all cells to build the col matrix
  fors(i, 1, n + 1) fors(j, 1, n + 1) {
    scanf("%d", &a[i][j]), sol(i, j); // compute for current cell
    
    int r = min(i, j); // max possible square size ending at (i,j)
    
    // If we have more than q colors, update min size required to exceed q
    if (col[i][j].size() > q)
      r = min(col[i][j][q].first - 1, r);
    
    d[1]++; // count of 1x1 subsquares
    d[r + 1]--; // subtract from larger size (to be added to smaller later)
  }
  
  // Compute the final answer by prefix sum
  fors(i, 1, n + 1) d[i] += d[i - 1], printf("%d\n", d[i]);
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/