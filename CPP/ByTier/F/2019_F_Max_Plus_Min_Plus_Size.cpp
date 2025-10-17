// Problem: CF 2019 F - Max Plus Min Plus Size
// https://codeforces.com/contest/2019/problem/F

/*
F. Max Plus Min Plus Size
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

The problem involves selecting a subset of elements in an array such that no two selected elements are adjacent,
and the score is defined as: max(selected) + min(selected) + count(selected).

This solution uses a greedy approach with a disjoint-set (DSU) data structure.
We process elements in decreasing order of value, merging intervals and tracking max/min information.

Time Complexity: O(n log n) due to sorting and DSU operations (amortized).
Space Complexity: O(n) for the DSU, arrays, and auxiliary structures.

Algorithms/Techniques: 
- Disjoint Set Union (DSU)
- Greedy algorithm
- Sorting
*/

#include <algorithm>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define mem(_B, _E, _S) (memset((_B), (_E), (_S) * sizeof(*_B)))
char Getchar() {
  static char buf[1 << 22], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
void read(int &t) {
  t = 0;
  char ch = Getchar();
  while (!isdigit(ch))
    ch = Getchar();
  while (isdigit(ch))
    t = t * 10 + ch - '0', ch = Getchar();
}
const int N = 2e5 + 10;
using LL = long long;
int a[N], id[N];
int res, tag; // res stores contribution from size, tag tracks max value of red elements
int fmx[2][N], siz[N], dsu[N], vis[N];
int mx; // maximum element in the current array
int Find(int x) { return x == dsu[x] ? x : dsu[x] = Find(dsu[x]); }
int chkmx(int x) { return (siz[x] & 1) ? fmx[1][x] : (fmx[0][x] | fmx[1][x]); }
void Upd(int x, int t) {
  res += t * (siz[x] + 1) / 2; // Update contribution from size
  tag += t * chkmx(x);         // Update max element in the group
}
void Merge(int x, int y) {
  x = Find(x), y = Find(y);
  if (x == y)
    return;
  Upd(x, -1), Upd(y, -1); // Remove contributions of old components before merging
  int o = siz[x] & 1;
  fmx[0][x] |= fmx[o][y];   // Update max in even positions
  fmx[1][x] |= fmx[o ^ 1][y]; // Update max in odd positions accordingly
  siz[x] += siz[y];        // Merge sizes
  dsu[y] = x;              // Union operation
  Upd(x, 1);               // Add updated contribution of merged component
}
void solve() {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i)
    read(a[i]);
  for (int i = 1; i <= n; ++i)
    id[i] = i, dsu[i] = i;
  // Sort indices by their corresponding values in descending order
  std::sort(id + 1, id + n + 1, [&](int i, int j) { return a[i] > a[j]; });
  mx = a[id[1]], res = tag = 0; // mx is highest value, initialize results
  int ans = 0;
  mem(fmx[0], 0, n + 1), mem(fmx[1], 0, n + 1); // Reset the max tracking arrays
  mem(vis, 0, n + 1);
  std::fill(siz + 1, siz + n + 1, 1); // Initially, all sets have size 1
  for (int i = 1; i <= n; ++i) {
    int x = id[i];
    vis[x] = 1;
    fmx[1][x] = a[x] == mx; // Mark if the element is max
    Upd(x, 1);             // Add contribution of single-node component
    if (x > 1 && vis[x - 1])
      Merge(x - 1, x);
    if (x < n && vis[x + 1])
      Merge(x, x + 1);
    ans = std::max(ans, mx + a[x] + res - (tag == 0)); // Update answer with current best
  }
  printf("%d\n", ans);
}
int main() {
  int T;
  read(T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/