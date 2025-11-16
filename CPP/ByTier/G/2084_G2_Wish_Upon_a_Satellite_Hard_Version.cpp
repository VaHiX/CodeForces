// Problem: CF 2084 G2 - Wish Upon a Satellite (Hard Version)
// https://codeforces.com/contest/2084/problem/G2

/*
Purpose: This code solves the problem of maximizing the beauty of a permutation, 
where beauty is defined as the sum of f(c) for all subsegments c of the permutation. 
The game played by Turtle and Piggy determines f(c) based on min/max operations on adjacent elements.

Algorithm: 
- The solution uses a Splay tree to maintain and update the structure of the permutation.
- The beauty is computed by processing elements in order and maintaining a value sum 
  using lazy propagation and tree traversal techniques.
- For each missing element, we decide whether to place it in an even or odd position 
  to maximize the overall beauty.

Time Complexity: O(n log n) per test case
Space Complexity: O(n)

The code processes each element in order and uses a splay tree to efficiently 
handle insertions and queries while maintaining the values required for the beauty computation.
*/
#include <cstdio>
#define ll long long
int read() {
  int num = 0;
  char ch;
  ch = getchar();
  while (ch < 48 || ch > 57)
    ch = getchar();
  while (ch > 47 && ch < 58) {
    num = (num << 1) + (num << 3) + (ch ^ 48);
    ch = getchar();
  }
  return num;
}
ll min(ll x, ll y) { return x < y ? x : y; }
ll max(ll x, ll y) { return x > y ? x : y; }
const int N = 5e5 + 15;
int n, m, cnt, rt, a[N], w[N];
struct node {
  int ch[2], fa, sz;
  ll tag1, tag2;
  ll val, lval;
  void clear() {
    ch[0] = ch[1] = fa = sz = 0;
    val = lval = 0;
    tag1 = tag2 = 0;
  }
} v[N];
void pushup(int x) {
  v[x].sz = v[v[x].ch[0]].sz + v[v[x].ch[1]].sz + 1;
  v[x].lval = v[x].val;
  if (v[x].ch[0])
    v[x].lval = v[v[x].ch[0]].lval;
}
void pushdown(int x) {
  if (v[x].ch[0]) {
    v[v[x].ch[0]].val += v[x].tag1 * v[v[v[x].ch[0]].ch[0]].sz + v[x].tag2;
    v[v[x].ch[0]].lval += v[x].tag2;
    v[v[x].ch[0]].tag1 += v[x].tag1;
    v[v[x].ch[0]].tag2 += v[x].tag2;
  }
  if (v[x].ch[1]) {
    v[v[x].ch[1]].val += v[x].tag1 * (v[v[x].ch[0]].sz + 1);
    v[v[x].ch[1]].val += v[x].tag1 * v[v[v[x].ch[1]].ch[0]].sz + v[x].tag2;
    v[v[x].ch[1]].lval += v[x].tag1 * (v[v[x].ch[0]].sz + 1) + v[x].tag2;
    v[v[x].ch[1]].tag1 += v[x].tag1;
    v[v[x].ch[1]].tag2 += v[x].tag1 * (v[v[x].ch[0]].sz + 1) + v[x].tag2;
  }
  v[x].tag1 = v[x].tag2 = 0;
}
void pd(int x) {
  if (x)
    pd(v[x].fa);
  pushdown(x);
}
bool get(int x) { return v[v[x].fa].ch[1] == x; }
void rotate(int x) {
  int y = v[x].fa, z = v[y].fa;
  bool X = get(x);
  if (z)
    v[z].ch[get(y)] = x;
  if (v[x].ch[X ^ 1])
    v[v[x].ch[X ^ 1]].fa = y;
  v[x].fa = z, v[y].fa = x;
  v[y].ch[X] = v[x].ch[X ^ 1];
  v[x].ch[X ^ 1] = y;
  pushup(y), pushup(x);
}
void splay(int x) {
  pd(x);
  while (v[x].fa) {
    if (v[v[x].fa].fa)
      rotate(get(x) == get(v[x].fa) ? v[x].fa : x);
    rotate(x);
  }
  rt = x;
}
void insert(int x) {
  if (!rt) {
    v[++cnt].clear();
    v[cnt].sz = 1;
    rt = cnt;
    return;
  }
  int now = rt;
  while (1) {
    pushdown(now);
    int X = 0, ls = now;
    if (v[v[now].ch[0]].sz > x) {
      X = 0, now = v[now].ch[0];
    } else {
      x -= v[v[now].ch[0]].sz + 1;
      X = 1, now = v[now].ch[1];
    }
    if (!now) {
      v[++cnt].clear();
      v[ls].ch[X] = cnt;
      v[cnt].fa = ls;
      v[cnt].sz = 1;
      splay(cnt);
      return;
    }
  }
}
int ask(int x, int s) {
  pushdown(x);
  if (v[x].ch[1] && v[v[x].ch[1]].lval <= 0)
    return ask(v[x].ch[1], s + v[v[x].ch[0]].sz + 1);
  if (v[x].val <= 0)
    return s + v[v[x].ch[0]].sz;
  return ask(v[x].ch[0], s);
}
ll st, ST, ans, S;
void Ask(int x, int s) {
  pushdown(x);
  if (v[x].ch[0])
    Ask(v[x].ch[0], s);
  s += v[v[x].ch[0]].sz;
  if (s <= m)
    ans -= v[x].val;
  s++;
  if (v[x].ch[1])
    Ask(v[x].ch[1], s);
}
int tt;
void work() {
  tt++;
  n = read(), ans = 0;
  m = n - n / 2, cnt = rt = st = 0;
  ST = 0;
  for (int i = 1; i <= n; i++)
    w[i] = -1;
  for (int i = 1; i <= n; i++) {
    ans += 1ll * i * i;
    a[i] = read();
    if (a[i])
      w[a[i]] = i % 2;
  }
  insert(0);
  for (int i = 0; i < n; i++) {
    ST += 2ll * (st - 1) * (st - 1) + 1ll * (-2 * i - (n % 2)) * (st - 1) +
          1ll * i * m;
    ll tag1 = 4, tag2 = st * 4 - 2 - 2 * i - (n % 2);
    v[rt].lval += tag2, v[rt].val += tag2 + v[v[rt].ch[0]].sz * tag1;
    v[rt].tag1 += tag1, v[rt].tag2 += tag2;
    pushdown(rt);
    if (w[i + 1] == 0)
      continue;
    if (w[i + 1] == 1) {
      st++;
      continue;
    }
    int u = ask(rt, 0);
    insert(u);
  }
  S = ST;
  Ask(rt, st);
  printf("%lld\n", ans - ST);
}
int main() {
  int Case = read();
  while (Case--)
    work();
}


// https://github.com/VaHiX/CodeForces/