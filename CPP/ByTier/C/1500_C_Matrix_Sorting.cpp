// Problem: CF 1500 C - Matrix Sorting
// https://codeforces.com/contest/1500/problem/C

/*
 * Code Purpose: 
 *   Determines if table A can be transformed into table B using a series of stable column sorts.
 *   If possible, outputs a sequence of columns to sort by.
 *
 * Algorithm:
 *   - Construct a topological order of columns based on the required relative ordering in B.
 *   - Use a greedy method to process columns in topological order.
 *   - Verify that the transformation is valid by reordering rows according to the column sort sequence.
 *
 * Time Complexity: O(H * W^2 + H^2 * W)
 *   - Building dependency graph: O(H * W)
 *   - Topological sort (BFS): O(W + H * W) = O(H * W)
 *   - Checking transformation correctness: O(H^2 * W)
 * 
 * Space Complexity: O(H * W)
 *   - Storage for matrices A, B, and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i, n) for (int i = 0; i < (n); i++)
int H, W;
vector<vector<int>> A, B;
vector<int> F_Row;        // Tracks which rows have not been processed yet
vector<int> C_Col;        // Counts dependencies for each column
vector<int> Ord;          // Stores the sorted column order
int main() {
  scanf("%d%d", &H, &W);
  A.assign(H, vector<int>(W));
  rep(y, H) rep(x, W) scanf("%d", &A[y][x]);
  B.assign(H, vector<int>(W));
  rep(y, H) rep(x, W) scanf("%d", &B[y][x]);
  
  F_Row.assign(H - 1, 1);   // Initially all row pairs are considered unprocessed
  C_Col.assign(W, 0);       // Initialize dependency count for each column
  rep(y, H - 1) rep(x, W) if (B[y][x] > B[y + 1][x]) C_Col[x]++; // Count needed inversions per column
  
  queue<int> Q;
  rep(x, W) if (C_Col[x] == 0) Q.push(x); // Start with columns that have no dependencies
    
  while (Q.size()) {
    int px = Q.front();
    Q.pop();
    Ord.push_back(px);  // Add to the ordered list of columns
    
    rep(y, H - 1) if (B[y][px] < B[y + 1][px]) // Process rows that are incorrectly ordered in this column
      if (F_Row[y]) {
        rep(x, W) if (B[y][x] > B[y + 1][x]) // Reduce dependency count for columns where values are out of order
          if ((--C_Col[x]) == 0) Q.push(x);
        F_Row[y] = 0; // Mark this row pair as processed
      }
  }
  
  reverse(Ord.begin(), Ord.end());  // Reverse to get final valid sorting order
  
  vector<pair<pair<int, int>, int>> P(H);  // Store row index and its current mapping
  rep(y, H) P[y].second = y;
  
  // Apply column sorts in the computed order
  for (int x : Ord) {
    rep(i, H) P[i].first = {A[P[i].second][x], i};  // Build key for sort (value, original index)
    sort(P.begin(), P.end());  // Stable sort by column value
  }
  
  // Check if the reordered rows match matrix B
  rep(i, H) rep(x, W) {
    int y = P[i].second;
    if (A[y][x] != B[i][x]) {
      printf("-1\n");
      return 0;
    }
  }
  
  printf("%d\n", (int)Ord.size());
  rep(i, Ord.size()) {
    if (i)
      printf(" ");
    printf("%d", Ord[i] + 1);  // Output column indices (1-based)
  }
  printf("\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/