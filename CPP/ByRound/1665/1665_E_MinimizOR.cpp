/*
 * Problem URL : https://codeforces.com/problemset/problem/1665/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
#define use 1, n, rt
#define left l, mid, ls[p]
#define righ mid + 1, r, rs[p]
#define N 400000 * 35
#define mod 998244353
#define fer(x, y, z) for (register int x = y; x <= z; x++)
using namespace std;
int lct, tr[N][2], sum[N], rt[110000];
int sta[110000], ss, n;
void sak_tr(int &p, int pr, int wei, int num) {
  p = ++lct;
  sum[p] = sum[pr] + 1;
  if (wei == 1)
    return;
  int to = ((num & (1 << wei - 2)) != 0);
  tr[p][to ^ 1] = tr[pr][to ^ 1];
  sak_tr(tr[p][to], tr[pr][to], wei - 1, num);
}
int sak_fi(int p, int pr, int wei, int num) {
  if (wei == 1)
    return num;
  int to = 1;
  if (sum[tr[p][0]] - sum[tr[pr][0]])
    to = 0;
  return sak_fi(tr[p][to], tr[pr][to], wei - 1, (num << 1) | to);
}
int sak_qu(int p, int pr, int wei, int num) {
  if (wei == 1)
    return num;
  int to, c1 = 0, c0 = 0;
  fer(i, 1, ss) if ((sta[i] & (1 << wei - 2)) != 0) c1++;
  else c0++;

  to = (sum[tr[p][0]] - sum[tr[pr][0]] + c0 <= 1);

  int res = 0;
  if (to == 0) {
    fer(i, 1, ss) if ((sta[i] & (1 << wei - 2)) == to) sta[++res] = sta[i];
    ss = res;
  }

  if (sum[tr[p][0]] - sum[tr[pr][0]] == 1 && c0 == 0)
    sta[++ss] = sak_fi(tr[p][0], tr[pr][0], wei - 1, num << 1);

  return sak_qu(tr[p][to], tr[pr][to], wei - 1, (num << 1) | to);
}
signed main() {
  int t;
  cin >> t;
  while (t--) {
    fer(i, 1, lct) sum[i] = tr[i][0] = tr[i][1] = 0;
    memset(rt, 0, n * 4 + 4), lct = 0;
    scanf("%d", &n);
    int x, l, r;
    fer(i, 1, n) scanf("%d", &x), sak_tr(rt[i], rt[i - 1], 33, x);
    int q;
    scanf("%d", &q);
    while (q--)
      scanf("%d%d", &l, &r), ss = 0,
                             printf("%d\n", sak_qu(rt[r], rt[l - 1], 33, 0));
  }
}
