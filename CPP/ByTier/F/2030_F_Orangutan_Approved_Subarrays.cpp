// Problem: CF 2030 F - Orangutan Approved Subarrays
// https://codeforces.com/contest/2030/problem/F

/* 
F. Orangutan Approved Subarrays
Algorithms/Techniques: Segment Tree with range maximum query and point update, Two-pointers technique.
Time Complexity: O(n log n + q log n) per test case
Space Complexity: O(n) per test case

The problem involves checking whether a subarray can be emptied by repeatedly removing 
consecutive elements of the same value if that value is still in a set S. 
This simulates a game where you remove all instances of some value from the array, 
if that value exists in the current set S.
We preprocess the entire array to determine for each position the leftmost valid starting index 
to match any previous occurrence of the same element. Then for each query, we use a segment tree 
to efficiently check the constraints against previously processed prefixes.

*/
#include <cstdio>
const int rSiz = 1 << 21;
char rBuf[rSiz], *p1 = rBuf, *p2 = rBuf;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = rBuf) + fread(rBuf, 1, rSiz, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
template <class T> void rd(T &x) {
  char ch = gc();
  for (; ch < '0' || ch > '9'; ch = gc())
    ;
  for (x = 0; ch >= '0' && ch <= '9'; ch = gc())
    x = (x << 1) + (x << 3) + (ch ^ 48);
}
#include <algorithm>
const int _ = 2e5 + 5;
int n, q, a[_], b[_], t[_ << 2], ans[_];
void Bld(int x, int l, int r) {
  t[x] = 0; // Initialize segment tree node
  if (l == r)
    return;
  int m = (l + r) >> 1;
  Bld(x << 1, l, m), Bld(x << 1 | 1, m + 1, r); // Build left and right subtrees
}
void Chg(int x, int l, int r, int w, int v) {
  if (l == r)
    return t[x] = v, void(); // Update the point in segment tree
  int m = (l + r) >> 1;
  if (w <= m)
    Chg(x << 1, l, m, w, v); // Go left if w is on left side
  else
    Chg(x << 1 | 1, m + 1, r, w, v); // Go right if w is on right side
  t[x] = std::max(t[x << 1], t[x << 1 | 1]); // Merge children for max value
}
int Qry(int x, int l, int r, int L, int R) {
  if (R < l || r < L)
    return 0; // Out of range
  if (L <= l && r <= R)
    return t[x]; // Fully inside query range
  int m = (l + r) >> 1;
  return std::max(Qry(x << 1, l, m, L, R), Qry(x << 1 | 1, m + 1, r, L, R)); // Query both sides
}
void solve() {
  rd(n), rd(q);
  Bld(1, 1, n); // Build segment tree
  for (int i = 1; i <= n; i++)
    rd(a[i]), b[i] = 0; // Read array and reset b[]
  for (int i = 1, l = 1, r; i <= n; i++) {
    r = b[a[i]]; // Get last occurrence of element a[i]
    for (; Qry(1, 1, n, l, r) > r; l++) // Adjust left pointer using segment tree
      ;
    if (r)
      Chg(1, 1, n, r, i); // Update position r in segment tree
    ans[i] = l; // Store answer for current prefix
    b[a[i]] = i; // Remember current index of a[i]
  }
  for (int i = 1, l, r; i <= q; i++) {
    rd(l), rd(r);
    if (l < ans[r])
      printf("NO\n"); // If left pointer is less than required start, impossible
    else
      printf("YES\n"); // Otherwise it's valid
  }
}
int main() {
  int T;
  rd(T);
  for (; T; T--)
    solve();
}


// https://github.com/VaHiX/codeForces/