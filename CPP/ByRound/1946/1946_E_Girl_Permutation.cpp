// Problem: CF 1946 E - Girl Permutation
// https://codeforces.com/contest/1946/problem/E

/*
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n) per test case
Space Complexity: O(n) for precomputed factorials and combinatorics

The problem involves finding the number of permutations of length n with given prefix and suffix maximum positions.
The approach uses dynamic programming to compute contributions from prefix and suffix maximums separately, 
then combines them using combinatorics (binomial coefficients).

Key insights:
1. The first element must be a prefix maximum (index 1)
2. The last element must be a suffix maximum (index n)
3. All prefix maxima must be in increasing order of index
4. All suffix maxima must be in increasing order of index
5. The prefix maximums and suffix maximums must intersect at exactly one point (the global maximum)
6. The number of valid permutations is computed by multiplying:
   - Ways to arrange elements before the prefix maximums
   - Ways to arrange elements after the suffix maximums
   - Ways to choose positions for the prefix maximums
*/

#include <stdio.h>
#include <utility>
#include <vector>

#define fir first
#define sec second
#ifdef LOCAL
#define dbg(x)                                                                 \
  cerr << "In Line " << __LINE__ << " the " << #x << " = " << x << '\n';
#define dpi(x, y)                                                              \
  cerr << "In Line " << __LINE__ << " the " << #x << " = " << x << " ; "       \
       << "the " << #y << " = " << y << '\n';
#define dbgf(fmt, args...) fprintf(stderr, fmt, ##args);
#else
#define dbg(x) void();
#define dpi(x, y) void();
#define dbgf(fmt, args...) void();
#endif
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using vi = vector<int>;
using vpii = vector<pii>;
bool Mbe;
constexpr int MOD = 1e9 + 7;
template <typename T> T add(T a, T b, T p = MOD) {
  return (a + b >= p) ? (a + b - p) : (a + b);
}
template <typename T> T del(T a, T b, T p = MOD) {
  return (a - b < 0) ? (a - b + p) : (a - b);
}
template <typename T> T mul(T a, T b, T p = MOD) { return 1ll * a * b % p; }
template <typename T> T cadd(T &a, T b, T p = MOD) { return a = add(a, b, p); }
template <typename T> T cdel(T &a, T b, T p = MOD) { return a = del(a, b, p); }
template <typename T> T cmul(T &a, T b, T p = MOD) { return a = mul(a, b, p); }
template <typename T> T cmax(T &a, T b) { return a = max(a, b); }
template <typename T> T cmin(T &a, T b) { return a = min(a, b); }
namespace FastIO {
constexpr int LEN = 1 << 20;
char in[LEN + 1], out[LEN + 1];
char *pin = in, *pout = out, *ein = in, *eout = out + LEN;
char gc() {
  return pin == ein && (ein = (pin = in) + fread(in, 1, LEN, stdin), ein == in)
             ? EOF
             : *pin++;
}
void pc(char c) {
  pout == eout && (fwrite(out, 1, LEN, stdout), pout = out);
  (*pout++) = c;
  return;
}
void Flush() {
  fwrite(out, 1, pout - out, stdout);
  pout = out;
}
template <typename T> T Read() {
  T x = 0;
  int f = 1;
  char ch = gc();
  while (ch < '0' || ch > '9')
    f = (ch == '-' ? (~f + 1) : f), ch = gc();
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
  return x * f;
}
template <typename T> void Write(T x, char c) {
  static char stk[40];
  int tp = 0;
  if (x < 0)
    pc('-'), x = ~x + 1;
  do
    stk[tp++] = x % 10 + 48, x /= 10;
  while (x);
  while (tp--)
    pc(stk[tp]);
  pc(c);
  return;
}
void Read(char *s) {
  char ch = gc();
  while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9')))
    ch = gc();
  while ((ch != EOF) && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
                         (ch >= '0' && ch <= '9')))
    *s = ch, s++, ch = gc();
  *s = '\0';
  return;
}
void Write(char *s) {
  while (*s != '\0')
    pc(*s), s++;
  return;
}
void Puts(char *s) {
  Write(s), pc('\n');
  return;
}
} // namespace FastIO
#define getchar FastIO::gc
#define putchar FastIO::pc
#define Flush FastIO::Flush
#define Read FastIO::Read
#define Write FastIO::Write
#define Puts FastIO::Puts
constexpr int MAXN = 2e5 + 5;
int n, m1, m2, p[MAXN], s[MAXN], fc[MAXN], ifc[MAXN], f[MAXN], g[MAXN];
int qpow(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1, cmul(a, a))
    if (b & 1)
      cmul(ans, a);
  return ans;
}
void Init(int N) {
  for (int i = fc[0] = 1; i <= N; i++)
    fc[i] = mul(fc[i - 1], i);
  ifc[N] = qpow(fc[N], MOD - 2);
  for (int i = N - 1; ~i; i--)
    ifc[i] = mul(ifc[i + 1], i + 1);
  return;
}
int C(int n, int m) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return mul(mul(fc[n], ifc[n - m]), ifc[m]);
}
void slv() {
  n = Read<int>(), m1 = Read<int>(), m2 = Read<int>();
  for (int i = 1; i <= m1; i++)
    p[i] = Read<int>();
  for (int i = 1; i <= m2; i++)
    s[i] = Read<int>();
  // Check if the constraints are valid:
  // First prefix max must be at index 1
  // Last suffix max must be at index n
  // Last prefix max must equal first suffix max
  if (p[m1] != s[1] || p[1] != 1 || s[m2] != n) {
    Puts("0");
    return;
  }
  // f[i] represents number of ways to place prefix maxima among [1, p[i]]
  f[1] = 1;
  for (int i = 2; i <= m1; i++)
    f[i] =
        mul(f[i - 1], mul(C(p[i] - 2, p[i - 1] - 1), fc[p[i] - p[i - 1] - 1]));
  // g[i] represents number of ways to place suffix maxima among [s[i], n]
  g[m2] = 1;
  for (int i = m2 - 1; i >= 1; i--)
    g[i] = mul(g[i + 1],
               mul(C(n - s[i] - 1, n - s[i + 1]), fc[s[i + 1] - s[i] - 1]));
  // Multiply all components together
  int ans = mul(mul(f[m1], g[1]), C(n - 1, p[m1] - 1));
  Write(ans, '\n');
  return;
}
void clr() { return; }
bool Med;
int main() {
#ifdef LOCAL
  freopen("!in.in", "r", stdin);
  freopen("!out.out", "w", stdout);
  fprintf(stderr, "%.3lf Mb\n", fabs((&Mbe - &Med) / 1048576.0));
#endif
  int T = Read<int>();
  Init(2e5);
  while (T--)
    slv(), clr();
  Flush();
#ifdef LOCAL
  fprintf(stderr, "%d ms\n", (int)clock());
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/