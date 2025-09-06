/*
 * Problem URL : https://codeforces.com/problemset/problem/2107/F2
 * Submit Date : 2025-08-17
 */

#define ssh(x) <x>
#include ssh(bits / stdc++.h)
#define rfor(x...) for (register x)
#define rep(i, l, r) rfor(ll i = l; i <= r; i++)
#define ref(i, l, r) rfor(ll i = l; i < r; i++)
#define per(i, l, r) rfor(ll i = l; i >= r; i--)
#define rev(i, u, v) rfor(ll i = head[u], v; v = to[i], i; i = next[i])
#define rej(i, s) rfor(ll i = s; i; i = (i - 1) & (s))
#define re0(i, s)rfor(ll i=s;~i;i=i?(i-1)&(s))
#define red(i, n) rfor(ll i = n; i; i >>= 1)
#define IO(x...)                                                               \
  ((*#x != '/' || #x[1]) &&                                                    \
   (*#x && freopen(#x ".in", "r", stdin) && freopen(#x ".out", "w", stdout),   \
    gc = fgc, pc = fpc, atexit(fout)))
typedef long long ll;
typedef unsigned long long ull;
typedef const ll cll;
cll N = 1e6 + 7, mod = 1e9 + 7, iv2 = (mod + 1) / 2, inf = 0x3f3f3f3f3f3f3f3f,
    root = 3, iz = 1 << 21, oz = 1 << 22;
typedef ll aN[N];
char is[iz], *i1 = is, *i2 = is, os[oz], *o1 = os, *o2 = os + oz;
int fgc() {
  return i1 == i2 && is == (i2 = is + fread(i1 = is, 1, iz, stdin)) ? -1
                                                                    : *i1++;
}
void fout() { fwrite(os, o1 - os, 1, stdout), o1 = os; }
int fpc(int c) {
  if (o1 == o2)
    fout();
  return *o1++ = c;
}
int (*gc)() = getchar, (*pc)(int) = putchar, wt[126];
int readchar(int l = 33, int r = 126) {
  if (l > r)
    std::swap(l, r);
  int c = gc();
  for (; c < l || c > r; c = gc())
    ;
  return c;
}
ll readll() {
  ll x = 0, w = 1;
  int c = gc();
  for (; c < 48 || c > 57; c = gc())
    c - 45 || (w = -w);
  for (; c > 47 && c < 58; c = gc())
    x = x * 10 + c - 48;
  return x * w;
}
void writell(cll u, int c = 32) {
  int t = 0;
  rfor(ull n = u < 0 ? pc(45), 0ull - u : u; n; n /= 10) wt[++t] = n % 10 ^ 48;
  for (t || pc(48); t;)
    pc(wt[t--]);
  c &&pc(c);
}
int mygets(char *s, int c = 0) {
  char *t = s + 1;
  while ((*s = gc()) < 33)
    ;
  while ((*t = gc()) > 32)
    t++;
  c && (*t++ = c), *t = 0;
  return t - s;
}
int myputs(const char *s, int c = 10) {
  const char *t = s;
  while (*t)
    pc(*t++);
  c &&pc(c);
  return t - s + (c != 0);
}
cll IO_res = IO(), T = readll();
#define debug(x, c) (void)0 // printf("%s=%lld%c",#x,x,c)
aN ct, vl, ps, sm;
struct slope {
  aN x, y;
  mutable ll h;
  ll t;
  void clear() { h = 1, t = 0; }
  void add(cll cx, cll cy) {
    // printf("add(%lld,%lld)\n",cx,cy);
    while (t && x[t] >= cx)
      t--;
    while (t > 1 &&
           (y[t] - cy) * (x[t] - x[t - 1]) >= (y[t - 1] - y[t]) * (cx - x[t]))
      t--;
    x[++t] = cx, y[t] = cy;
    if (t <= h + 1)
      h = t;
  }
  ll query(cll u) const {
    // printf("query u=%lld %lld %lld %lld\n",u,h,x[h],y[h]);
    while (h > 1 && u * x[h] + y[h] >= u * x[h - 1] + y[h - 1])
      h--;
    // printf("query u=%lld %lld %lld %lld\n",u,h,x[h],y[h]);
    return u * x[h] + y[h];
  }
} q;
void calc(cll ID) {
  (void)ID;
  cll n = readll();
  ll t = 0, sum = 0;
  q.clear();
  rep(i, 1, n) {
    cll u = readll();
    sum += u;
    while (t && u < vl[t])
      sum += (ps[t] - ps[t - 1]) * (u + 1) -
             ((ps[t] - ps[t - 1]) * (vl[t] + 1) - ct[t]),
          t--;
    if (t && u == vl[t])
      ps[t] = i, ct[t]++, sm[t] = sum,
      q.add(vl[t] + 2, sm[t] - ps[t] * (vl[t] + 2));
    else
      vl[++t] = u, ps[t] = i, ct[t] = 1, sm[t] = sum,
      q.add(vl[t] + 2, sm[t] - ps[t] * (vl[t] + 2));
    writell(q.query(ps[t]), i == n ? 10 : 32);
  }
}
int main() {
  rep(i, 1, T) calc(i);
  return 0;
}
/*
1
10
2 4 5 4 3 3 3 3 3 3
*/
