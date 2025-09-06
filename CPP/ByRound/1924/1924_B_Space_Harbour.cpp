/*
 * Problem URL : https://codeforces.com/problemset/problem/1924/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>
const int N = 300002;
typedef long long ll;
int n, m, q, i, j, k, x[N], v, V[N];
int op[N], A[N], B[N], fa[N], l[N], L, R;
ll s[N], S[N], Ans[N];
int p(int x) { return fa[x] == x ? x : fa[x] = p(fa[x]); }
void add(int x, ll y) {
  s[x] += y;
  while (x <= n)
    S[x] += y, x += x & -x;
}
ll sum(int x) {
  ll su = 0;
  while (x)
    su += S[x], x -= x & -x;
  return su;
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (i = 1; i <= m; i++)
    scanf("%d", x + i);
  for (i = 1; i <= m; i++) {
    scanf("%d", &v);
    V[x[i]] = v;
  }
  for (i = 1; i <= q; i++) {
    scanf("%d%d%d", op + i, A + i, B + i);
    if (op[i] == 1)
      V[A[i]] = B[i];
  }
  for (i = 1; i <= n; i++)
    fa[i] = i;
  for (i = 1; i <= n; i++) {
    l[i] = V[i - 1] ? i - 1 : l[i - 1];
    if (V[i] == 0)
      fa[i] = i + 1;
    else
      add(i, 1ll * V[l[i]] * (i - l[i]) * (i - l[i] - 1) / 2);
  }
  for (k = q; k; k--)
    if (op[k] == 1) {
      i = A[k];
      j = p(i + 1);
      add(i, -1ll * V[l[i]] * (i - l[i]) * (i - l[i] - 1) / 2);
      add(j, -1ll * V[l[j]] * (j - l[j]) * (j - l[j] - 1) / 2);
      V[i] = 0;
      fa[i] = i + 1;
      l[j] = l[i];
      add(j, 1ll * V[l[j]] * (j - l[j]) * (j - l[j] - 1) / 2);
    } else {
      L = A[k];
      R = B[k];
      i = p(L);
      j = l[p(R)];
      if (i > j)
        Ans[k] =
            1ll * V[j] *
            (1ll * (i - L) * (i - L + 1) / 2 - 1ll * (i - R) * (i - R - 1) / 2);
      else {
        Ans[k] = sum(j) - sum(i);
        Ans[k] += 1ll * V[l[i]] * (i - L) * (i - L + 1) / 2;
        i = p(R);
        Ans[k] +=
            1ll * V[j] *
            (1ll * (i - j) * (i - j - 1) / 2 - 1ll * (i - R) * (i - R - 1) / 2);
      }
    }
  for (k = 1; k <= q; k++)
    if (op[k] == 2)
      printf("%lld\n", Ans[k]);
}
