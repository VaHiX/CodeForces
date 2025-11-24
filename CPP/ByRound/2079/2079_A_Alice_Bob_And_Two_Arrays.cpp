// Problem: CF 2079 A - Alice, Bob, And Two Arrays
// https://codeforces.com/contest/2079/problem/A

/*
Algorithm/Techniques: Dynamic Programming with Segment Tree and Coordinate Compression
Time Complexity: O(N * M + Q * log Q + Q * log(N * M))
Space Complexity: O(N * M + Q)

This code solves a game theory problem where Alice and Bob play a turn-based game on two arrays.
The game involves building a subsequence that is valid for both arrays. The key insight is to use
dynamic programming with segment trees to efficiently calculate game states.

The approach involves:
1. Parsing input arrays in compressed segment format
2. Preprocessing all possible game states using dynamic programming
3. Using coordinate compression to reduce the state space
4. Segment tree operations to efficiently query and update game states
5. Sorting queries for efficient processing
*/

#include <stdio.h>
#include <string.h>
#define N 1600
#define M 1600
#define K 1600
#define Q 1000000
#define M_ (N * M + Q)
#define INF 0x3f3f3f3f
int min(int a, int b) { return a < b ? a : b; }
unsigned int Z = 12345;
int rand_() { return (Z *= 3) >> 1; }
int n, m, m_, q, k;
int aa[N], lla[N], xxa[N + 1]; // Arrays for storing segments and cumulative lengths of array a
int bb[M], llb[M], xxb[M + 1]; // Arrays for storing segments and cumulative lengths of array b
int ssa[K], ssb[K], yy_[K];    // Arrays for tracking cumulative counts and offset values
int xxa1[Q], xxb1[Q], ii[Q], jj[Q], gg[Q]; // Input coordinates and sorting arrays
char yes[Q];                   // Output array indicating winner for each query
int yy[M_], yy1[M_], idx[M_];  // Coordinate compression arrays
int compare_ij(int g1, int g2) {
  return ii[g1] != ii[g2] ? ii[g2] - ii[g1] : jj[g2] - jj[g1];
}
void sort(int *hh, int l, int r) {
  while (l < r) {
    int i = l, j = l, k = r, h = hh[l + rand_() % (r - l)], tmp;
    while (j < k) {
      int c = compare_ij(hh[j], h);
      if (c == 0)
        j++;
      else if (c < 0) {
        tmp = hh[i], hh[i] = hh[j], hh[j] = tmp;
        i++, j++;
      } else {
        k--;
        tmp = hh[j], hh[j] = hh[k], hh[k] = tmp;
      }
    }
    sort(hh, l, i);
    l = k;
  }
}
void sort_(int *hh, int m) {
  static int hh_[M_], kk[(1 << 16) + 1];
  int h, a;
  memset(kk, 0, sizeof kk);
  for (h = 0; h < m; h++)
    kk[(yy[hh[h]] & (1 << 16) - 1) + 1]++;
  for (a = 1; a < 1 << 16; a++)
    kk[a] += kk[a - 1];
  for (h = 0; h < m; h++)
    hh_[kk[yy[hh[h]] & (1 << 16) - 1]++] = hh[h];
  memset(kk, 0, sizeof kk);
  for (h = 0; h < m; h++)
    kk[(yy[hh_[h]] >> 16) + 1]++;
  for (a = 1; a < 1 << 16; a++)
    kk[a] += kk[a - 1];
  for (h = 0; h < m; h++)
    hh[kk[yy[hh_[h]] >> 16]++] = hh_[h];
}
int search(int y) {
  int lower, upper, h;
  lower = -1, upper = m_;
  while (upper - lower > 1) {
    h = (lower + upper) / 2;
    if (yy[h] <= y)
      lower = h;
    else
      upper = h;
  }
  return lower;
}
int st[M_ * 2];
void update(int c, int yl, int yr, int v) {
  int l = search(yy_[c] + yl - 1) + 1, r = search(yy_[c] + yr);
  for (l += m_, r += m_; l <= r; l >>= 1, r >>= 1) {
    if ((l & 1) == 1)
      st[l++] = v;
    if ((r & 1) == 0)
      st[r--] = v;
  }
}
int query(int i, int c, int xa, int xb) {
  int v, xa_, xb_;
  v = INF;
  for (i += m_; i > 0; i >>= 1)
    v = min(v, st[i]);
  if (v == INF) {
    xa_ = ssa[c], xb_ = ssb[c];
    if (xa_ - xb_ < xa - xb)
      xb_ = xa_ + xb - xa;
    else
      xa_ = xb_ + xa - xb;
  } else {
    xa_ = xxa[v / m], xb_ = xxb[v % m];
    if (xa_ - xb_ < xa - xb)
      xa_ = xb_ + xa - xb;
    else
      xb_ = xa_ + xb - xa;
  }
  return (xa_ - xa) % 2 == 0 ? 1 : 0;
}
int main() {
  static int hh[M_], ii_[K], jj_[K];
  static char dp[N][M];
  int g, g_, h, i, j, c, lower, upper, cnt;
  scanf("%*d%d%*d%d%d%d", &n, &m, &k, &q);
  for (i = 0; i < n; i++) {
    scanf("%d%d", &lla[i], &aa[i]), aa[i]--;
    xxa[i + 1] = xxa[i] + lla[i];
  }
  for (j = 0; j < m; j++) {
    scanf("%d%d", &llb[j], &bb[j]), bb[j]--;
    xxb[j + 1] = xxb[j] + llb[j];
  }
  for (g = 0; g < q; g++) {
    scanf("%d%d", &xxa1[g], &xxb1[g]);
    lower = 0, upper = n;
    while (upper - lower > 1) {
      i = (lower + upper) / 2;
      if (xxa[i] <= xxa1[g])
        lower = i;
      else
        upper = i;
    }
    i = lower;
    xxa1[g] -= xxa[i], ii[g] = i;
    lower = 0, upper = m;
    while (upper - lower > 1) {
      j = (lower + upper) / 2;
      if (xxb[j] <= xxb1[g])
        lower = j;
      else
        upper = j;
    }
    j = lower;
    xxb1[g] -= xxb[j], jj[g] = j;
  }
  for (i = 0; i < n; i++) {
    c = aa[i];
    xxa[i] = ssa[c], ssa[c] += lla[i];
  }
  for (j = 0; j < m; j++) {
    c = bb[j];
    xxb[j] = ssb[c], ssb[c] += llb[j];
  }
  for (g = 0; g < q; g++)
    xxa1[g] += xxa[ii[g]], xxb1[g] += xxb[jj[g]];
  yy_[0] = ssb[0];
  for (c = 1; c < k; c++)
    yy_[c] = yy_[c - 1] + ssa[c - 1] + ssb[c] + 1;
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      if (aa[i] == bb[j])
        yy[i * m + j] = yy_[aa[i]] + xxa[i] - xxb[j], hh[m_++] = i * m + j;
  for (g = 0; g < q; g++)
    yy[n * m + g] = yy_[aa[ii[g]]] + xxa1[g] - xxb1[g], hh[m_++] = n * m + g;
  sort_(hh, m_);
  for (h = 0; h < m_; h++)
    yy1[h] = yy[hh[h]], idx[hh[h]] = h;
  memcpy(yy, yy1, m_ * sizeof *yy1);
  memset(st, 0x3f, m_ * 2 * sizeof *st);
  memset(ii_, -1, k * sizeof *ii_);
  for (g = 0; g < q; g++)
    gg[g] = g;
  sort(gg, 0, q);
  g = 0;
  for (i = n - 1; i >= 0; i--) {
    memset(jj_, -1, k * sizeof *jj_);
    for (j = m - 1, cnt = 0; j >= 0; j--) {
      c = bb[j];
      if (ii_[c] != -1 && jj_[c] != -1 && !dp[ii_[c]][jj_[c]])
        cnt--;
      if (aa[i] == c) {
        while (g < q && ii[gg[g]] == i && jj[gg[g]] == j) {
          g_ = gg[g++];
          if (cnt > 0 || !query(idx[n * m + g_], c, xxa1[g_], xxb1[g_]))
            yes[g_] = 1;
        }
        if (cnt > 0)
          update(c, xxa[i] - (xxb[j] + llb[j] - 1),
                 (xxa[i] + lla[i] - 1) - xxb[j], i * m + j);
        dp[i][j] = query(idx[i * m + j], c, xxa[i], xxb[j]);
      }
      jj_[c] = j;
      if (ii_[c] != -1 && jj_[c] != -1 && !dp[ii_[c]][jj_[c]])
        cnt++;
    }
    c = aa[i];
    ii_[c] = i;
  }
  for (g = 0; g < q; g++)
    printf(yes[g] ? "Yes\n" : "No\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/