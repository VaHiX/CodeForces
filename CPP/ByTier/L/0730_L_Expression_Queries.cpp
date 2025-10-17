/*
 * Problem URL : https://codeforces.com/contest/730/problem/L
 * Submit Date : 2025-09-09
 */

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 400500
#define mod 1000000007
struct sth {
  int fg, v1, v2, v3;
};
struct node {
  int l, r;
  sth tp;
} e[N * 4];
struct qu1 {
  int l, r, id;
};
vector<qu1> qu[N];
int n, q, l, r, st[N], ct, bel[N], pw[N], su[N], lb[N], rb[N], as[N], v1[N],
    sl[N], sr[N], tp[N], vl[N];
char s[N];
int calc(int l, int r) {
  return (su[r] - 1ll * su[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}
sth subexpression(sth s1, sth s2, int fg) {
  sth s3;
  if (s1.fg && s2.fg && fg) {
    s3.v1 = s3.v2 = 1ll * s1.v1 * s2.v2 % mod;
    s3.v3 = 0;
    s3.fg = 1;
    return s3;
  }
  s3.fg = 0;
  if (s1.fg && fg)
    s3.v1 = 1ll * s1.v1 * s2.v1 % mod;
  else
    s3.v1 = s1.v1;
  if (s2.fg && fg)
    s3.v2 = 1ll * s1.v2 * s2.v2 % mod;
  else
    s3.v2 = s2.v2;
  s3.v3 = (s1.v3 + s2.v3) % mod;
  if (!s1.fg && !s2.fg && fg)
    s3.v3 = (s3.v3 + 1ll * s1.v2 * s2.v1) % mod;
  else {
    if (!s1.fg && (!s2.fg || !fg))
      s3.v3 = (s3.v3 + s1.v2) % mod;
    if (!s2.fg && (!s1.fg || !fg))
      s3.v3 = (s3.v3 + s2.v1) % mod;
  }
  return s3;
}
void update(int x) {
  int mid = (e[x].l + e[x].r) >> 1;
  e[x].tp =
      subexpression(e[x << 1].tp, e[x << 1 | 1].tp, s[tp[mid + 1]] == '*');
}
void create(int x, int l, int r) {
  e[x].l = l;
  e[x].r = r;
  if (l == r) {
    e[x].tp = (sth){1, vl[l], vl[l], 0};
    return;
  }
  int mid = (l + r) >> 1;
  create(x << 1, l, mid);
  create(x << 1 | 1, mid + 1, r);
  update(x);
}
sth request(int x, int l, int r) {
  if (e[x].l == l && e[x].r == r)
    return e[x].tp;
  int mid = (e[x].l + e[x].r) >> 1;
  if (mid >= r)
    return request(x << 1, l, r);
  else if (mid < l)
    return request(x << 1 | 1, l, r);
  else
    return subexpression(request(x << 1, l, mid),
                         request(x << 1 | 1, mid + 1, r),
                         s[tp[mid + 1]] == '*');
}
void findResult(int l, int r) {
  int ct = 0, ls = r;
  for (int i = r - 1; i >= l; i--)
    if (s[i] == ')')
      findResult(lb[i], i), i = lb[i];
    else if (s[i] == '+' && s[i] == '-')
      ls = i;
    else
      sr[i] = ls;
  ls = l;
  for (int i = l + 1; i <= r; i++)
    if (s[i] == '(')
      i = rb[i];
    else if (s[i] == '+' || s[i] == '*')
      tp[++ct] = i, ls = i;
    else
      sl[i] = ls;
  tp[0] = l;
  tp[ct + 1] = r;
  for (int i = 0; i <= ct; i++)
    if (s[tp[i] + 1] == '(')
      vl[i] = v1[tp[i] + 1];
    else
      vl[i] = calc(tp[i] + 1, tp[i + 1] - 1);
  create(1, 0, ct);
  for (int i = 0; i < qu[l].size(); i++) {
    int l1 = qu[l][i].l, r1 = qu[l][i].r, id = qu[l][i].id;
    int l2 = lower_bound(tp, tp + ct + 1, l1) - tp,
        r2 = lower_bound(tp, tp + ct + 1, r1) - tp;
    if (l2 == r2) {
      as[id] = calc(l1, r1);
      if (s[tp[l2 - 1] + 1] == '(')
        as[id] = vl[l2 - 1];
      continue;
    }
    int lv = calc(l1, tp[l2] - 1), rv = calc(tp[r2 - 1] + 1, r1);
    if (s[tp[l2 - 1] + 1] == '(')
      lv = vl[l2 - 1];
    if (s[tp[r2 - 1] + 1] == '(')
      rv = vl[r2 - 1];
    if (l2 + 1 == r2) {
      int fg = s[tp[l2]] == '*';
      if (fg)
        as[id] = 1ll * lv * rv % mod;
      else
        as[id] = (lv + rv) % mod;
      continue;
    }
    sth v0 = request(1, l2, r2 - 2);
    v0 = subexpression((sth){1, lv, lv, 0}, v0, s[tp[l2]] == '*');
    v0 = subexpression(v0, (sth){1, rv, rv, 0}, s[tp[r2 - 1]] == '*');
    as[id] = v0.fg ? v0.v1 : (1ll * v0.v1 + (!v0.fg) * v0.v2 + v0.v3) % mod;
  }
  sth v0 = request(1, 0, ct);
  v1[l] = (1ll * v0.v1 + (!v0.fg) * v0.v2 + v0.v3) % mod;
}
int main() {
  scanf("%s", s + 2);
  s[1] = '(';
  n = strlen(s + 1) + 1;
  s[n] = ')';
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = 10ll * pw[i - 1] % mod;
    su[i] = 10ll * su[i - 1] % mod;
    bel[i] = st[ct];
    if (s[i] == '(')
      st[++ct] = i;
    else if (s[i] == ')')
      rb[st[ct]] = i, lb[i] = st[ct], ct--, bel[i] = st[ct];
    else if (s[i] >= '0' && s[i] <= '9')
      su[i] = (su[i] + s[i] - '0') % mod;
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &l, &r);
    l++;
    r++;
    if (bel[l] != bel[r] || s[l] == '*' || s[l] == '+' || s[r] == '*' ||
        s[r] == '+' || s[l] == ')' || s[r] == '(')
      as[i] = -1;
    else
      qu[bel[l]].push_back((qu1){l, r, i});
  }
  findResult(1, n);
  for (int i = 1; i <= q; i++)
    printf("%d\n", as[i]);
} /*1695090492.1153603*/