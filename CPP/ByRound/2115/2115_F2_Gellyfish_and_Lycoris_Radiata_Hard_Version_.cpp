/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/F2
 * Submit Date : 2025-08-16
 */

/* https://codeforces.com/blog/entry/143418?#comment-1280710 (Nachia) */
#include <stdio.h>
#include <stdlib.h>

#define M 300000
#define Q 300000
#define N_ (1 << 19) /* N_ = pow2(ceil(log2(Q + 1))) */

int min(int a, int b) { return a < b ? a : b; }

int m;

int type[Q], xx[Q], q;

int n_;
int nn[N_ * 2];
int *xxl[N_ * 2], *xxr[N_ * 2], *aal[N_ * 2], *aar[N_ * 2];
char *on[N_ * 2];
int *jjl[N_ * 2], *jjr[N_ * 2], *ppl[N_ * 2], *ppr[N_ * 2];

void pul(int u) {
  static int xx[M + 1], kkl[M + 1], kkr[M + 1], jj[M + 1];
  int i, i_, i1, j, j_, j1, l, r, k, kl, kr, x;

  l = u << 1, r = l | 1;
  i = 0, j = 0, k = 0;
  while (i <= nn[l] && j <= nn[r]) {
    x = min(xxr[l][i], xxl[r][j]);
    xx[k] = x;
    if (xxr[l][i] == x)
      kkl[i++] = k;
    if (xxl[r][j] == x)
      kkr[j++] = k;
    k++;
  }
  nn[u] = k - 1;
  xxr[u] = (int *)malloc((nn[u] + 1) * sizeof *xxr[u]);
  ppr[u] = (int *)malloc(nn[u] * sizeof *ppr[u]);
  jjl[r] = (int *)malloc(nn[r] * sizeof *jjl[r]);
  jjr[r] = (int *)malloc(nn[r] * sizeof *jjr[r]);
  for (j = 0, j_ = 0; j < nn[r]; j++) {
    j1 = aar[r][j] >> 1, kl = kkr[j1], kr = kkr[j1 + 1];
    jjl[r][j] = j_;
    if ((aar[r][j] & 1) == 0)
      for (k = kl; k < kr; k++) {
        jj[k] = j_ << 1 | 0;
        ppr[u][j_] = j, xxr[u][j_] = xxr[r][j] + xx[k] - xx[kl], j_++;
      }
    else
      for (k = kr - 1; k >= kl; k--) {
        jj[k] = j_ << 1 | 1;
        ppr[u][j_] = j, xxr[u][j_] = xxr[r][j] + xx[kr] - xx[k + 1], j_++;
      }
    jjr[r][j] = j_;
  }
  xxr[u][nn[u]] = m;
  xxl[u] = (int *)malloc((nn[u] + 1) * sizeof *xxl[u]);
  aal[u] = (int *)malloc(nn[u] * sizeof *aal[u]);
  aar[u] = (int *)malloc(nn[u] * sizeof *aar[u]);
  ppl[u] = (int *)malloc(nn[u] * sizeof *ppl[u]);
  on[u] = (char *)malloc(nn[u] * sizeof *on[u]);
  jjl[l] = (int *)malloc(nn[l] * sizeof *jjl[l]);
  jjr[l] = (int *)malloc(nn[l] * sizeof *jjr[l]);
  for (i = 0, i_ = 0; i < nn[l]; i++) {
    i1 = aal[l][i] >> 1, kl = kkl[i1], kr = kkl[i1 + 1];
    jjl[l][i1] = i_;
    if ((aal[l][i] & 1) == 0)
      for (k = kl; k < kr; k++) {
        j_ = jj[k] >> 1;
        if ((jj[k] & 1) == 0)
          aal[u][i_] = j_ << 1 | 0, aar[u][j_] = i_ << 1 | 0;
        else
          aal[u][i_] = j_ << 1 | 1, aar[u][j_] = i_ << 1 | 1;
        ppl[u][j_] = i1, on[u][j_] = on[l][ppl[u][j_]] || on[r][ppr[u][j_]];
        xxl[u][i_] = xxl[l][i] + xx[k] - xx[kl], i_++;
      }
    else
      for (k = kr - 1; k >= kl; k--) {
        j_ = jj[k] >> 1;
        if ((jj[k] & 1) == 0)
          aal[u][i_] = j_ << 1 | 1, aar[u][j_] = i_ << 1 | 1;
        else
          aal[u][i_] = j_ << 1 | 0, aar[u][j_] = i_ << 1 | 0;
        ppl[u][j_] = i1, on[u][j_] = on[l][ppl[u][j_]] || on[r][ppr[u][j_]];
        xxl[u][i_] = xxl[l][i] + xx[kr] - xx[k + 1], i_++;
      }
    jjr[l][i1] = i_;
  }
  xxl[u][nn[u]] = m;
}

void add(int h) {
  int u = n_ + h;

  if (type[h] == 1) {
    nn[u] = xx[h] == m ? 1 : 2;
    xxl[u] = (int *)malloc((nn[u] + 1) * sizeof *xxl[u]);
    xxr[u] = (int *)malloc((nn[u] + 1) * sizeof *xxr[u]);
    aal[u] = (int *)malloc(nn[u] * sizeof *aal[u]);
    aar[u] = (int *)malloc(nn[u] * sizeof *aar[u]);
    on[u] = (char *)malloc(nn[u] * sizeof *on[u]);
    xxl[u][0] = xxr[u][0] = 0, xxl[u][1] = xxr[u][1] = xx[h];
    aal[u][0] = aar[u][0] = 0 << 1 | 0;
    on[u][0] = 1;
    if (xx[h] < m) {
      xxl[u][2] = xxr[u][2] = m;
      aal[u][1] = aar[u][1] = 1 << 1 | 0;
      on[u][1] = 0;
    }
  } else if (type[h] == 2) {
    nn[u] = xx[h] == m ? 1 : 2;
    xxl[u] = (int *)malloc((nn[u] + 1) * sizeof *xxl[u]);
    xxr[u] = (int *)malloc((nn[u] + 1) * sizeof *xxr[u]);
    aal[u] = (int *)malloc(nn[u] * sizeof *aal[u]);
    aar[u] = (int *)malloc(nn[u] * sizeof *aar[u]);
    on[u] = (char *)malloc(nn[u] * sizeof *on[u]);
    xxl[u][0] = xxr[u][0] = 0, xxl[u][1] = xxr[u][1] = xx[h];
    aal[u][0] = aar[u][0] = 0 << 1 | 1;
    on[u][0] = 0;
    if (xx[h] < m) {
      xxl[u][2] = xxr[u][2] = m;
      aal[u][1] = aar[u][1] = 1 << 1 | 0;
      on[u][1] = 0;
    }
  } else {
    nn[u] = 1;
    xxl[u] = (int *)malloc((nn[u] + 1) * sizeof *xxl[u]);
    xxr[u] = (int *)malloc((nn[u] + 1) * sizeof *xxr[u]);
    aal[u] = (int *)malloc(nn[u] * sizeof *aal[u]);
    aar[u] = (int *)malloc(nn[u] * sizeof *aar[u]);
    on[u] = (char *)malloc(nn[u] * sizeof *on[u]);
    xxl[u][0] = xxr[u][0] = 0, xxl[u][1] = xxr[u][1] = m;
    aal[u][0] = aar[u][0] = 0 << 1 | 0;
    on[u][0] = 0;
  }
  while (u > 1 && (u & 1) != 0)
    pul(u >>= 1);
}

void purge(int u, int i) {
  int v, l, r, j, j_;

  on[u][i] = 0;
  if (jjl[u] == NULL)
    return;
  v = u >> 1, l = v << 1, r = l | 1;
  for (j = jjl[u][i]; j < jjr[u][i]; j++) {
    j_ = (u & 1) != 0 ? j : aal[v][j] >> 1;
    if (!on[l][ppl[v][j_]] && !on[r][ppr[v][j_]])
      purge(v, j_);
  }
}

int search(int u, int x) {
  int lower = 0, upper = nn[u];

  while (upper - lower > 1) {
    int j = (lower + upper) / 2;

    if (xxr[u][j] <= x)
      lower = j;
    else
      upper = j;
  }
  return lower;
}

int query(int r, int x) {
  int l, u, i, j, j_;

  l = 0, u = -1, j_ = -1;
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1)
    if ((r & 1) == 0) {
      j = search(r, x);
      if (on[r][j])
        u = r, j_ = j;
      i = aar[r][j] >> 1;
      x = (aar[r][j] & 1) == 0 ? xxl[r][i] + x - xxr[r][j]
                               : xxl[r][i + 1] - 1 - (x - xxr[r][j]);
      r--;
    }
  if (u == -1)
    return 0;
  j = j_;
  while (u < n_)
    if (on[u << 1 | 0][ppl[u][j]])
      j = ppl[u][j], u = u << 1 | 0;
    else
      j = ppr[u][j], u = u << 1 | 1;
  return u - n_ + 1;
}

int main() {
  int h, x, ans;

  scanf("%d%d", &m, &q);
  n_ = 1;
  while (n_ <= q)
    n_ <<= 1;
  ans = 0;
  for (h = 0; h < q; h++) {
    scanf("%d%d%d", &type[h], &xx[h], &x), xx[h]--, x--;
    if (type[h] == 1 || type[h] == 2)
      xx[h] = (xx[h] + ans) % m + 1;
    else
      xx[h] = (xx[h] + ans) % q;
    add(h);
    if (type[h] == 3 && xx[h] < h && type[xx[h]] == 1)
      type[xx[h]] = 0, purge(n_ + xx[h], 0);
    x = (x + ans) % m;
    printf("%d\n", ans = query(h, x));
  }
  return 0;
}
