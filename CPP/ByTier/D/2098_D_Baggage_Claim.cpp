// Problem: CF 2098 D - Baggage Claim
// https://codeforces.com/contest/2098/problem/D

/*
 * Problem: D. Baggage Claim
 * Purpose: Given a grid of size n x m and a sequence of odd-indexed nodes of a path,
 *          determine the number of valid ways to complete the path such that it forms
 *          a simple path with adjacent cells sharing a side.
 *
 * Algorithms/Techniques:
 *  - Union-Find (Disjoint Set Union) for tracking connected components and node counts
 *  - Coordinate compression and validation using Manhattan distance checks
 *  - Modular arithmetic for large result handling
 *
 * Time Complexity:
 *  - For each test case: O(k * α(n*m)) where α is the inverse Ackermann function,
 *    due to union-find operations.
 *  - Overall: O(t * k * α(n*m)), with total nm up to 10^6
 *
 * Space Complexity:
 *  - O(n * m) for storing parent and count arrays, and the grid state vector
 */

#include <math.h>
#include <stdio.h>
#include <bits/std_abs.h>
#include <vector>

#define int long long
using namespace std;
vector<int> p;     // Parent array for Union-Find
vector<int> cnt;   // Count array to track component sizes or flags
int fp(int x) {
  if (x == p[x])
    return x;
  return p[x] = fp(p[x]);  // Path compression
}
int fu(int a, int b) {
  int pa = fp(a);
  int pb = fp(b);
  // If both components are either empty or forbidden, set new parent to empty
  if ((cnt[pa] == 0 || cnt[pa] == -2) && (cnt[pb] == 0 || cnt[pb] == -2)) {
    cnt[pa] = 0;
    p[pb] = pa;
    return 0;
  } else if (cnt[pb] == 0 || cnt[pa] == 0)
    cnt[pa] = 0;   // If one is empty, mark it as empty
  else if (pa == pb || cnt[pa] == -2 || cnt[pb] == -2)
    cnt[pa] = -2;  // Mark as forbidden if already marked or same component
  else
    cnt[pa] += cnt[pb];  // Merge components and sum counts
  p[pb] = pa;
  return 1;
}
signed main() {
  int t;
  scanf("%lld", &t);
  while (t--) {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    vector<int> v(n * m + 1, 0);  // Visited array to track cells in path
    p.clear();
    cnt.clear();
    p.resize(n * m + 1);
    cnt.resize(n * m + 1, 1);     // Initialize all counts to 1
    for (int i = 1; i <= n * m; i++)
      p[i] = i;
    int res = 1;                  // Result counter
    int bx, by;
    scanf("%lld %lld", &bx, &by);
    v[(bx - 1) * m + by] = 1;     // Mark starting point
    for (int i = 1; i <= k; i++) {
      int x, y;
      scanf("%lld %lld", &x, &y);
      int a = (x - 1) * m + y;    // Convert 2D to 1D index
      
      // Check if move is valid (manhattan distance == 2)
      if ((bx + by) % 2 != (x + y) % 2)
        res = 0;
      if (abs(x - bx) + abs(y - by) != 2)
        res = 0;

      // If cell already visited, path invalid
      if (v[a] == 1)
        res = 0;

      // If move is straight (horizontal or vertical), check intermediate cell
      if (x - bx == 0 || y - by == 0) {
        int a1 = ((x + bx) / 2 - 1) * m + (y + by) / 2;  // Midpoint for straight line moves
        if (cnt[fp(a1)] == 0 || cnt[fp(a1)] == -2)
          res = 0;
        cnt[fp(a1)] = 0;  // Mark midpoint as unavailable
      } else {
        // Diagonal move: two possible intermediate paths, use Union-Find to merge
        int a1 = (x - 1) * m + by;
        int a2 = (bx - 1) * m + y;
        res *= fu(a1, a2);
      }
      v[a] = 1;  // Mark current cell as visited
      bx = x;    // Update current position
      by = y;
    }

    // Final count of valid paths from valid root components
    for (int i = 1; i <= n * m; i++) {
      if (p[i] == i && cnt[i] != 0)      // If root node and not forbidden
        res *= abs(cnt[i]);              // Multiply by component size (absolute value)
      while (res < 0)
        res += 1000000007;
      res %= 1000000007;                 // Modular result
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/