// Problem: CF 2153 F - Odd Queries on Odd Array
// https://codeforces.com/contest/2153/problem/F

// Problem: F. Odd Queries on Odd Array
// Algorithms/Techniques: Square Root Decomposition with Preprocessing for Fast Query Answering
// Time Complexity: O(n*sqrt(n) + q*sqrt(n)) where n is array length, q is number of queries
// Space Complexity: O(n*sqrt(n) + n) for precomputed answers and bitsets

#include <stdio.h>
#include <bitset>
#include <utility>

constexpr int B = 500;
int T, n, nn, bn, q, a[512000];
long long ve, ans[1280][1280];
std::bitset<512000> ae, d[1280];

// Updates the active elements and their sum for range [l,r)
void load(int l, int r) {
  for (int k = l; k < r; k++)
    if (ae[a[k]])
      ve -= a[k], ae[a[k]] = false;
    else
      ve += a[k], ae[a[k]] = true;
}

// Resets or toggles elements in range [l,r) based on precomputed bitsets d[0] and d[1]
void clean(int l, int r, int x, int y) {
  if (x == y)
    for (int k = l; k < r; k++)
      ae[a[k]] = false;
  else
    for (int k = l; k < r; k++)
      ae[a[k]] = d[x][a[k]] ^ d[y][a[k]];
}

// Computes the beauty of the subarray [l,r)
long long query(int l, int r) {
  int lb = l / B, rb = r / B;
  if (lb == rb)
    ve = 0, clean(l, r, 0, 0), load(l, r);
  else {
    int lbr = lb * B + B, rbl = rb * B;
    ve = ans[lb + 1][rb], clean(l, lbr, lb, rb - 1), clean(rbl, r, lb, rb - 1),
    load(l, lbr), load(rbl, r);
  }
  return ve;
}

int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d%d", &nn, &q), bn = (nn - 1) / B + 1, n = bn * B;
    for (int i = 0; i < nn; i++)
      scanf("%d", &a[i]);
    for (int i = nn; i < n; i++)
      a[i] = 1;
    ae.reset();
    for (int i = 0; i < bn; i++) {
      int nbl = i * B, nbr = i * B + B;
      for (int j = nbl; j < nbr; j++)
        ae[a[j]] = !ae[a[j]];
      d[i] = ae;
    }
    ve = 0, ae.reset();
    for (int i = 0; i < bn; i++)
      if (i % 2 == 0)
        for (int j = i + 1; j <= bn; j++)
          load(j * B - B, j * B), ans[i][j] = ve;
      else {
        load(i * B - B, i * B);
        for (int j = bn; j > i; j--)
          ans[i][j] = ve, load(j * B - B, j * B);
      }
    long long lst = 0;
    for (int l, r; q--;) {
      scanf("%d%d", &l, &r), l = (l - 1 + lst) % nn + 1,
                             r = (r - 1 + lst) % nn + 1;
      if (l > r)
        std::swap(l, r);
      l--, printf("%lld ", lst = query(l, r));
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/