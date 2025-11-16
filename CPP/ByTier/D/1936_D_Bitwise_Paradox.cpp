// Problem: CF 1936 D - Bitwise Paradox
// https://codeforces.com/contest/1936/problem/D

/*
 * Problem: D. Bitwise Paradox
 * 
 * Purpose: This code solves a dynamic programming problem involving bitwise OR operations on intervals
 * and finding the minimum beauty among all good intervals in a given range.
 *  
 * Approach:
 *  - Segment Tree with interval merging logic
 *  - Each node stores information about:
 *    - Minimum beauty (an): for good intervals
 *    - Maximum beauty (mx): for current interval
 *    - ml: prefix information for bitwise OR
 *    - mr: suffix information for bitwise OR  
 *    - sl, sr: sizes of ml and mr arrays
 *  - For each query update or range query:
 *    - Update value in segment tree
 *    - Query over range to get minimum beauty among good intervals
 * 
 * Time Complexity:
 *  - Build: O(n)
 *  - Update: O(log n)
 *  - Query: O(log^2 n) per query (due to merging logic)
 *  - Overall per test case: O(n log n + q log^2 n)
 * 
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
int n, V;
#define F first
#define S second
#define pi pair<int, int>
#define mp make_pair

// Structure to store interval information
struct info {
  int an;           // minimum beauty of good intervals in this segment
  pi ml[35], mr[35]; // prefix and suffix OR info with max element
  int sl, sr, mx;   // sizes of ml/mr arrays and maximum element in segment
};

// Operator to merge two interval info structures
info operator+(const info &a, const info &b) {
  info c;
  c.an = min(a.an, b.an), c.mx = max(a.mx, b.mx);
  int sl = a.sl, sr = b.sr;
  
  // Copy prefix from left
  for (int i = 0; i < sl; i++)
    c.ml[i] = a.ml[i];
  
  // Extend prefix with right segment if OR increases
  int X = c.ml[sl - 1].F, T = a.mx;
  for (int i = 0; i < b.sl; i++) {
    if ((X | b.ml[i].F) > X)
      X |= b.ml[i].F, c.ml[sl++] = mp(X, max(T, b.ml[i].S));
  }
  
  // Copy suffix from right  
  for (int i = 0; i < sr; i++)
    c.mr[i] = b.mr[i];
  
  // Extend suffix with left segment if OR increases
  X = c.mr[sr - 1].F, T = b.mx;
  for (int i = 0; i < a.sr; i++) {
    if ((X | a.mr[i].F) > X)
      X |= a.mr[i].F, c.mr[sr++] = mp(X, max(T, a.mr[i].S));
  }
  
  c.sl = sl, c.sr = sr;
  
  // Merge prefix and suffix to check for valid intervals  
  for (int i = a.sr - 1, j = 0; i >= 0; i--) {
    while (j < b.sl && (a.mr[i].F | b.ml[j].F) < V)
      j++;
    if (j == b.sl)
      break;
    c.an = min(c.an, max(b.ml[j].S, a.mr[i].S));
  }
  return c;
}

// Segment tree structure
info o[800100], fz;
bool oo;
int a[201000], b[201000];

// Query function to get info for a range [x,y]
void ask(int p, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    if (oo)
      fz = fz + o[p];
    else
      fz = o[p], oo = 1;
    return;
  }
  int mid = (l + r) >> 1;
  if (x <= mid)
    ask(p << 1, l, mid, x, y);
  if (y > mid)
    ask(p << 1 | 1, mid + 1, r, x, y);
}

const int I = (1 << 30) + 20;

// Update function for point updates
void up(int p, int l, int r, int x, int z) {
  if (l == r) {
    b[l] = z;
    o[p].an = (b[l] >= V) ? a[l] : I;  // If b[i] >= V, then it's good
    o[p].mx = a[l];
    o[p].sl = o[p].sr = 1, o[p].ml[0] = o[p].mr[0] = mp(b[l], a[l]);  // Initialize prefix/suffix
    return;
  }
  int mid = (l + r) >> 1;
  if (x <= mid)
    up(p << 1, l, mid, x, z);
  else
    up(p << 1 | 1, mid + 1, r, x, z);
  o[p] = o[p << 1] + o[p << 1 | 1];  // Merge children
}

// Build segment tree
void build(int p, int l, int r) {
  if (l == r) {
    o[p].an = (b[l] >= V) ? a[l] : I;
    o[p].mx = a[l];
    o[p].sl = o[p].sr = 1, o[p].ml[0] = o[p].mr[0] = mp(b[l], a[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
  o[p] = o[p << 1] + o[p << 1 | 1];
}

// Process one test case
void sol() {
  scanf("%d%d", &n, &V);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]);
  build(1, 1, n);
  int q;
  scanf("%d", &q);
  for (int i = 1, x, z, l, r, ty; i <= q; i++) {
    scanf("%d", &ty);
    if (ty == 1)
      scanf("%d%d", &x, &z), up(1, 1, n, x, z);
    else {
      oo = 0;
      scanf("%d%d", &l, &r), ask(1, 1, n, l, r);
      if (fz.an >= I)
        printf("-1 ");
      else
        printf("%d ", fz.an);
    }
  }
  puts("");
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/