// Problem: CF 2018 E1 - Complex Segments (Easy Version)
// https://codeforces.com/contest/2018/problem/E1

/*
E1. Complex Segments (Easy Version)
Purpose: Find the maximum size of a complex subset of given segments.
A set of segments is complex if they can be partitioned into subsets such that:
1. All subsets have the same size.
2. Two segments intersect if and only if they are in the same subset.

Algorithms/Techniques:
- Coordinate compression
- Binary search on answer (using solve function with divide and conquer)
- Union-Find (Disjoint Set Union) for grouping segments
- Sorting segments by right endpoint

Time Complexity: O(n^2 * log n) per test case due to sorting, coordinate compression, and binary search over possible group sizes.
Space Complexity: O(n) for storing segments and auxiliary arrays.

*/

#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <utility>
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
using namespace std;

const int maxn = 4e4 + 5;
int n, t, res;
int c[maxn], f[maxn]; // c: coordinate compression array; f: DSU parent array
pii p[maxn];          // p: segments stored as pairs (left, right)

// Find root of x with path compression
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

// Calculate maximum number of groups size m that can be formed
int calc(int m) {
  int cnt = 0;
  for (int i = 1, x = 0, cur = 0, lim = 0, lst = 0; i <= n; i++) {
    int l = p[i].fi, r = p[i].se;
    if (l <= lim) // Skip segments already considered in current group
      continue;
    for (int j = lst + 1; j < r; j++)
      f[j] = lst; // Connect all points between last and current right endpoint to last point
    cur++, lst = f[r] = r, x = find(l); // Increment group count, update last processed point, find root of left
    if (x > lim)  // If root exceeds the limit (meaning we cannot merge this into existing group)
      cur--, f[x] = x - 1;  // Decrement group count and adjust DSU structure
    if (cur == m)  // If current group has reached required size
      cnt++, cur = 0, lim = r; // Increment total group count, reset counters
  }
  res = max(res, cnt * m); // Update global maximum with product of group count and size
  return cnt;
}

// Binary search on the answer using divide and conquer to find best grouping
void solve(int l, int r, int L, int R) {
  if (l > r || L == R)  // Base case: if invalid range or no more splits possible
    return;
  int mid = (l + r) >> 1, val = calc(mid);  // Try mid as current group size and get how many groups we can make
  solve(l, mid - 1, L, val), solve(mid + 1, r, val, R);  // Recurse on left and right halves with updated bounds
}

int main() {
  for (scanf("%d", &t); t--;) {
    scanf("%d", &n), memset(c, 0, 8 * n), res = 0;  // Initialize data structures per test case
    
    // Read segment left endpoints and mark occurrences in coordinate array
    for (int i = 1; i <= n; i++)
      scanf("%d", &p[i].fi), c[p[i].fi]++;
    
    // Read segment right endpoints and mark occurrences in coordinate array
    for (int i = 1; i <= n; i++)
      scanf("%d", &p[i].se), c[p[i].se]++;
      
    // Compute prefix sum to allow coordinate compression
    for (int i = 1; i <= 2 * n; i++)
      c[i] += c[i - 1];
      
    // Convert original coordinates into compressed ones (right end)
    for (int i = 1; i <= n; i++)
      p[i].se = c[p[i].se]--;
      
    // Convert original coordinates into compressed ones (left end)
    for (int i = 1; i <= n; i++)
      p[i].fi = c[p[i].fi]--;
      
    sort(p + 1, p + n + 1, [&](pii x, pii y) { return x.se < y.se; }); // Sort by right endpoint ascending
    
    solve(1, n, n + 1, 0); // Binary search over group sizes from 1 to n
    printf("%d\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/