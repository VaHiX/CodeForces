// Problem: CF 1919 F1 - Wine Factory (Easy Version)
// https://codeforces.com/contest/1919/problem/F1

#pragma GCC optimize(2)
#include <stdio.h>
#include <string>

#define LL long long
using namespace std;
const int Rea = 1e5 + 3;
bool ifnum(char x) { return x >= '0' && x <= '9'; }
bool ifupchr(char x) { return x >= 'A' && x <= 'Z'; }
bool iflochr(char x) { return x >= 'a' && x <= 'z'; }
struct Rin {
  char c;
  char gc() {
    static char rea[Rea];
    static char *head, *tail;
    return head == tail && (tail = (head = rea) + fread(rea, 1, Rea, stdin),
                            head == tail)
               ? EOF
               : *head++;
  }
  Rin &operator>>(int &x) {
    bool tag = false;
    x = 0;
    for (c = gc(); c > '9' || c < '0'; c = gc())
      if (c == '-') {
        c = gc();
        tag = true;
        break;
      }
    for (; c >= '0' && c <= '9'; c = gc())
      x = (x << 1) + (x << 3) + (c ^ '0');
    if (tag)
      x = -x;
    return *this;
  }
  Rin &operator>>(LL &x) {
    bool tag = false;
    x = 0;
    for (c = gc(); c > '9' || c < '0'; c = gc())
      if (c == '-') {
        c = gc();
        tag = true;
        break;
      }
    for (; c >= '0' && c <= '9'; c = gc())
      x = (x << 1) + (x << 3) + (c ^ '0');
    if (tag)
      x = -x;
    return *this;
  }
  Rin &operator>>(char &x) {
    for (c = gc(); !ifnum(c) && !iflochr(c) && !ifupchr(c); c = gc())
      ;
    x = c;
    return *this;
  }
  Rin &operator>>(string &x) {
    x.clear();
    for (c = gc(); !ifnum(c) && !iflochr(c) && !ifupchr(c); c = gc())
      ;
    for (; ifnum(c) || iflochr(c) || ifupchr(c); c = gc())
      x.push_back(c);
    return *this;
  }
} rin;
#define rin(x) rin >> x
void jh(int &x, int &y) {
  if (x ^ y)
    x ^= y ^= x ^= y;
  return;
}
void jh(LL &x, LL &y) {
  if (x ^ y)
    x ^= y ^= x ^= y;
  return;
}
int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }
LL min(LL x, LL y) { return x < y ? x : y; }
LL max(LL x, LL y) { return x > y ? x : y; }
const int M = 998244353;
#define lmod(i)                                                                \
  if (i < 0)                                                                   \
  i += M
#define rmod(i)                                                                \
  if (i >= M)                                                                  \
  i -= M
int ksm(int x, int y) {
  int ans = 1;
  for (; y; y >>= 1) {
    if (y & 1)
      ans = 1LL * ans * x % M;
    x = 1LL * x * x % M;
  }
  return ans;
}
void ad(int &x, int y) {
  x += y;
  rmod(x);
  return;
}
void ac(int &x, int y) {
  x -= y;
  lmod(x);
  return;
}
int aad(int x, int y) {
  x += y;
  rmod(x);
  return x;
}
int aac(int x, int y) {
  x -= y;
  lmod(x);
  return x;
}
#define yes                                                                    \
  {                                                                            \
    puts("YES");                                                               \
    return;                                                                    \
  }
#define no                                                                     \
  {                                                                            \
    puts("NO");                                                                \
    return;                                                                    \
  }
const int N = 5e5 + 3;
int n, q;
int a[N];
int b[N];
LL c[N];
#define ls (i << 1)
#define rs (i << 1 | 1)
struct node {
  LL v1, v2, v;
  int l, r;
} t[N << 2];
// 更新节点信息, 维护前缀满足条件的节点数量和后缀满足条件的节点数量
void up(int i) {
  t[i].v1 = t[ls].v1;
  t[i].v2 = t[rs].v2;
  t[i].v = t[ls].v + t[rs].v + min(t[ls].v2, t[rs].v1);
  if (t[ls].v2 > t[rs].v1)
    t[i].v2 += t[ls].v2 - t[rs].v1;
  else
    t[i].v1 += t[rs].v1 - t[ls].v2;
  return;
}
// 初始化线段树叶子节点值
void maketree(int l, int r, int i) {
  t[i].l = l;
  t[i].r = r;
  if (l == r) {
    if (a[l] >= b[l])
      t[i].v2 = a[l] - b[l], t[i].v1 = 0, t[i].v = b[l];
    else
      t[i].v1 = b[l] - a[l], t[i].v2 = 0, t[i].v = a[l];
    return;
  }
  int mid = l + r >> 1;
  maketree(l, mid, ls);
  maketree(mid + 1, r, rs);
  up(i);
  return;
}
// 递归更新线段树节点
void change(int l, int r, int i, int pos) {
  if (l == r) {
    if (a[l] >= b[l])
      t[i].v2 = a[l] - b[l], t[i].v1 = 0, t[i].v = b[l];
    else
      t[i].v1 = b[l] - a[l], t[i].v2 = 0, t[i].v = a[l];
    return;
  }
  int mid = l + r >> 1;
  if (pos <= mid)
    change(l, mid, ls, pos);
  else
    change(mid + 1, r, rs, pos);
  up(i);
  return;
}
// 主处理函数
void work() {
  rin >> n >> q;
  for (int i = 1; i <= n; i++)
    rin >> a[i];
  for (int i = 1; i <= n; i++)
    rin >> b[i];
  for (int i = 1; i < n; i++)
    rin >> c[i];
  maketree(1, n, 1);
  for (; q; q--) {
    int pos;
    LL x, y, z;
    rin >> pos >> x >> y >> z;
    a[pos] = x;
    b[pos] = y;
    change(1, n, 1, pos);
    printf("%lld\n", t[1].v);
  }
  return;
}
int main() {
  work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/