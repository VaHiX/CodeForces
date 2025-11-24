// Problem: CF 1866 F - Freak Joker Process
// https://codeforces.com/contest/1866/problem/F

/*
Code Purpose:
This is a solution to the "Freak Joker Process" problem. It efficiently handles dynamic updates to player stats (A and B values) and computes overall rankings after each query. The algorithm uses a technique called "offline processing with block decomposition" to optimize the updates and queries.

Key Algorithms / Techniques:
1. Offline processing with block decomposition: Groups queries into blocks to reduce the overhead of recalculating ranks.
2. Coordinate compression and prefix sums: Used to quickly compute rankings.
3. Sorting and Binary search: Efficiently handles rank computations.

Time Complexity: O((N + Q) * sqrt(Q) * log(N)) where N is the number of players and Q is the number of queries.
Space Complexity: O(N + Q) for storing data structures and intermediate arrays.

*/

#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <utility>

using namespace std;
#define mp make_pair
#define fr first
#define sc second
const long long sqn = 316, ma = 1e5;
long long n, nn, nm[2], sza[2][369], a[2][100069], ps[2][100069], kd[100069],
    ex[369], pst[2][369], od[2][100069], fq[369][369], vl[2][369][100069],
    ps2[200069];
pair<long long, pair<long long, long long>> qq[100069];
bitset<100069> spc[2];
inline void slv(long long lb, long long rb) {
  long long rr, i, j, ii, u, ky, k, l, w, e, p, y, x, z;
  for (ii = 0; ii < 2; ii++) {
    for (i = 1; i <= ma; i++) {
      ps[ii][i] = 0;
    }
    for (i = 1; i <= n; i++) {
      ps[ii][a[ii][i]]++;
    }
    for (i = 1; i <= ma; i++) {
      ps[ii][i] += ps[ii][i - 1];
    }
  }
  for (i = 1; i <= n; i++) {
    kd[i] = 5;
  }
  for (ii = 0; ii < 2; ii++) {
    spc[ii].reset();
  }
  for (rr = lb; rr <= rb; rr++) {
    ky = qq[rr].fr;
    k = qq[rr].sc.fr;
    u = qq[rr].sc.sc;
    if (ky <= 2) {
      e = ky - 1;
      l = a[e][k] - (u == -1);
      kd[k] = 1;
      spc[e][l] = 1;
      a[e][k] += u;
    }
  }
  for (rr = rb; rr >= lb; rr--) {
    ky = qq[rr].fr;
    k = qq[rr].sc.fr;
    u = qq[rr].sc.sc;
    if (ky <= 2) {
      e = ky - 1;
      a[e][k] -= u;
    }
  }
  nn = 0;
  for (i = 1; i <= n; i++) {
    if (kd[i] != 1) {
      if (spc[0][a[0][i]] && spc[1][a[1][i]]) {
        kd[i] = 2;
      } else if (spc[0][a[0][i]]) {
        kd[i] = 3;
      } else if (spc[1][a[1][i]]) {
        kd[i] = 4;
      }
    } else {
      nn++;
      ex[nn] = i;
    }
  }
  for (ii = 0; ii < 2; ii++) {
    nm[ii] = 0;
    for (i = 1; i <= ma; i++) {
      od[ii][i] = 0;
      if (spc[ii][i]) {
        nm[ii]++;
        pst[ii][nm[ii]] = i;
        od[ii][i] = nm[ii];
      }
    }
    for (i = 1; i <= nm[ii]; i++) {
      sza[ii][i] = 0;
    }
  }
  for (i = 1; i <= nm[0]; i++) {
    for (j = 1; j <= nm[1]; j++) {
      fq[i][j] = 0;
    }
  }
  for (i = 1; i <= n; i++) {
    if (kd[i] == 2) {
      fq[od[0][a[0][i]]][od[1][a[1][i]]]++;
    } else if (kd[i] == 3 || kd[i] == 4) {
      e = kd[i] - 3;
      p = od[e][a[e][i]];
      sza[e][p]++;
      vl[e][p][sza[e][p]] = n - ps[!e][a[!e][i]] + 1;
    }
  }
  for (ii = 0; ii < 2; ii++) {
    for (i = 1; i <= nm[ii]; i++) {
      sort(vl[ii][i] + 1, vl[ii][i] + sza[ii][i] + 1);
    }
  }
  for (i = 1; i <= n * 2; i++) {
    ps2[i] = 0;
  }
  for (i = 1; i <= n; i++) {
    if (kd[i] == 2 || kd[i] == 5) {
      ps2[n - ps[0][a[0][i]] + 1 + n - ps[1][a[1][i]] + 1]++;
    }
  }
  for (i = 1; i <= n * 2; i++) {
    ps2[i] += ps2[i - 1];
  }
  for (rr = lb; rr <= rb; rr++) {
    ky = qq[rr].fr;
    k = qq[rr].sc.fr;
    u = qq[rr].sc.sc;
    if (ky <= 2) {
      e = ky - 1;
      l = a[e][k] - (u == -1);
      p = od[e][l];
      for (i = 1; i <= nm[!e]; i++) {
        y = p;
        x = i;
        if (e) {
          swap(y, x);
        }
        w = n - ps[0][pst[0][y]] + 1 + n - ps[1][pst[1][x]] + 1;
        ps2[w - (u == -1)] -= fq[y][x] * u;
      }
      a[e][k] += u;
      ps[e][l] -= u;
    } else {
      w = n - ps[0][a[0][k]] + 1 + n - ps[1][a[1][k]] + 1;
      z = ps2[w - 1] + 1;
      for (i = 1; i <= nn; i++) {
        z += n - ps[0][a[0][ex[i]]] + 1 + n - ps[1][a[1][ex[i]]] + 1 < w;
      }
      for (ii = 0; ii < 2; ii++) {
        for (i = 1; i <= nm[ii]; i++) {
          p = lower_bound(vl[ii][i] + 1, vl[ii][i] + sza[ii][i] + 1,
                          w - (n - ps[ii][pst[ii][i]] + 1)) -
              vl[ii][i] - 1;
          z += p;
        }
      }
      printf("%lld\n", z);
    }
  }
}
int main() {
  long long t, rr, i, ii, u, ky, k, c = 0, b4 = 0;
  char ch;
  scanf("%lld", &n);
  for (ii = 0; ii < 2; ii++) {
    for (i = 1; i <= n; i++) {
      scanf("%lld", &a[ii][i]);
    }
  }
  scanf("%lld", &t);
  for (rr = 1; rr <= t; rr++) {
    scanf("%lld%lld", &ky, &k);
    if (ky <= 2) {
      scanf(" %c", &ch);
      u = (ch == '+') - (ch == '-');
      qq[rr] = {ky, {k, u}};
    } else {
      qq[rr] = {ky, {k, 0}};
    }
    if (c == sqn && ky <= 2) {
      slv(b4 + 1, rr - 1);
      c = 0;
      b4 = rr - 1;
    }
    c += ky <= 2;
  }
  slv(b4 + 1, t);
}


// https://github.com/VaHiX/CodeForces/