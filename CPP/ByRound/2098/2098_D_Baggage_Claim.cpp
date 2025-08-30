/*
 * Problem URL : https://codeforces.com/problemset/problem/2098/D
 * Submit Date : 2025-08-20
 */

#include <math.h>
#include <stdio.h>
#include <vector>
#define int long long
using namespace std;
/// D. Baggage Claim

vector<int> p;
vector<int> cnt;

int fp(int x) {
  if (x == p[x])
    return x;
  return p[x] = fp(p[x]);
}

int fu(int a, int b) {
  int pa = fp(a);
  int pb = fp(b);

  if ((cnt[pa] == 0 || cnt[pa] == -2) && (cnt[pb] == 0 || cnt[pb] == -2)) {
    cnt[pa] = 0;
    p[pb] = pa;
    return 0;
  } else if (cnt[pb] == 0 || cnt[pa] == 0)
    cnt[pa] = 0;
  else if (pa == pb || cnt[pa] == -2 || cnt[pb] == -2)
    cnt[pa] = -2;
  else
    cnt[pa] += cnt[pb];
  p[pb] = pa;
  return 1;
}

signed main() {
  int t;
  scanf("%lld", &t);
  while (t--) {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    vector<int> v(n * m + 1, 0);
    p.clear();
    cnt.clear();
    p.resize(n * m + 1);
    cnt.resize(n * m + 1, 1);
    for (int i = 1; i <= n * m; i++)
      p[i] = i;
    int res = 1;
    int bx, by;
    scanf("%lld %lld", &bx, &by);
    v[(bx - 1) * m + by] = 1;
    for (int i = 1; i <= k; i++) {
      int x, y;
      scanf("%lld %lld", &x, &y);
      int a = (x - 1) * m + y;
      if ((bx + by) % 2 != (x + y) % 2)
        res = 0;
      if (abs(x - bx) + abs(y - by) != 2)
        res = 0;
      if (v[a] == 1)
        res = 0;

      if (x - bx == 0 || y - by == 0) {
        int a1 = ((x + bx) / 2 - 1) * m + (y + by) / 2;
        if (cnt[fp(a1)] == 0 || cnt[fp(a1)] == -2)
          res = 0;
        cnt[fp(a1)] = 0;
      } else {
        int a1 = (x - 1) * m + by;
        int a2 = (bx - 1) * m + y;
        res *= fu(a1, a2);
      }
      v[a] = 1;
      bx = x;
      by = y;
    }
    for (int i = 1; i <= n * m; i++) {
      if (p[i] == i && cnt[i] != 0)
        res *= abs(cnt[i]);
      while (res < 0)
        res += 1000000007;
      res %= 1000000007;
    }
    printf("%lld\n", res);
  }
  return 0;
}
