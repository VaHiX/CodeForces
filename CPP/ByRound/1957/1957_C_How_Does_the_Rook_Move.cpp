// Problem: CF 1957 C - How Does the Rook Move?
// https://codeforces.com/contest/1957/problem/C

/*
 * Problem: C. How Does the Rook Move?
 * Algorithm: Dynamic Programming with combinatorics
 * Time Complexity: O(n) per test case, where n is the board size
 * Space Complexity: O(n) for DP array and auxiliary arrays
 *
 * The problem involves placing rooks on an n×n chessboard such that no two
 * rooks attack each other (same row or column). You and the computer alternate
 * turns: you place a white rook, then the computer places a black rook at the
 * mirrored position (r,c) => (c,r), unless r == c, in which case the computer
 * skips its turn.
 *
 * After k moves, we determine how many valid final configurations are possible.
 * Key insight:
 * - Each rook placed by you also forces a mirrored move by the computer.
 * - This creates pairs of "constrained" rows/columns (r,c) where r != c.
 * - For each such pair, there are two options: either place a rook in row r or row c.
 * - For symmetric positions (r == c), only one option exists.
 * - The problem reduces to a dynamic programming recurrence on available "slots"
 *   (unconstrained rows/columns) to count valid configurations.
 *
 * The recurrence DP(x) represents number of ways to place rooks on x independent
 * pairs of rows/columns:
 *   DP(x) = (2*(x-1)*DP(x-2) + DP(x-1)) % MOD
 *   Base cases: DP(0) = 1, DP(1) = 1
 */

#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
#define srep(i, l, r) for (int i = l; i < r; i++)
#define sper(i, r, l) for (int i = r; i > l; i--)
#define erep(i, x) for (int i = h[x]; i; i = e[i].next)
#define erep2(i, x) for (int &i = cur[x]; i; i = e[i].next)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define fi first
#define se second
#define ui unsigned int
#define ld long double
#define pb push_back
#define pc putchar
#define lowbit(x) (x & -x)
#define maxbuf 2000020
#define gc()                                                                   \
  ((p1 == p2 &&                                                                \
    (p2 = (p1 = buffer) + fread(buffer, 1, maxbuf, stdin), p1 == p2))          \
       ? EOF                                                                   \
       : *p1++)
using namespace std;
namespace Fast_Read {
char buffer[maxbuf], *p1, *p2;
template <class T> void read_signed(T &x) {
  char ch = gc();
  x = 0;
  bool f = 1;
  while (!isdigit(ch) && ch != '-')
    ch = gc();
  if (ch == '-')
    f = 0, ch = gc();
  while ('0' <= ch && ch <= '9')
    x = (x << 1) + (x << 3) + ch - '0', ch = gc();
  x = (f) ? x : -x;
}
template <class T, class... Args> void read_signed(T &x, Args &...args) {
  read_signed(x), read_signed(args...);
}
template <class T> void read_unsigned(T &x) {
  char ch = gc();
  x = 0;
  while (!isdigit(ch))
    ch = gc();
  while (isdigit(ch))
    x = (x << 1) + (x << 3) + ch - '0', ch = gc();
}
template <class T, class... Args> void read_unsigned(T &x, Args &...args) {
  read_unsigned(x), read_unsigned(args...);
}
#define isletter(ch) ('a' <= ch && ch <= 'z')
int read_string(char *s) {
  char ch = gc();
  int l = 0;
  while (!isletter(ch))
    ch = gc();
  while (isletter(ch))
    s[l++] = ch, ch = gc();
  s[l] = '\0';
  return l;
}
} // namespace Fast_Read
using namespace Fast_Read;
int _num[20];
template <class T> void write(T x, char sep = '\n') {
  if (!x) {
    putchar('0'), putchar(sep);
    return;
  }
  if (x < 0)
    putchar('-'), x = -x;
  int c = 0;
  while (x)
    _num[++c] = x % 10, x /= 10;
  while (c)
    putchar('0' + _num[c--]);
  putchar(sep);
}
#define read read_signed
#define reads read_string
#define writes puts
#define maxn 400024
#define maxm
#define maxs
#define maxb
#define inf
#define eps
#define M 1000000007
#define ll long long int
int n, k, T;
int a[maxn][2];
bool vis[maxn];
int dp[maxn];
// DP(x): number of ways to arrange rooks on x independent rows/columns
int DP(int x) {
  if (vis[x])
    return dp[x];
  if (x <= 1)
    return 1;
  int &ans = dp[x];
  ans = 0;
  vis[x] = 1;
  // Recurrence based on combinatoric reasoning:
  // We can either extend previous solution by choosing any of (x-1) valid positions,
  // and placing a rook in the newly available pair or take the previous one
  ans = (2ll * (x - 1) * DP(x - 2) % M + DP(x - 1) % M) % M;
  return ans;
}
int main() {
  int Ti;
  read(Ti);
  for (T = 1; T <= Ti; T++) {
    read(n, k);
    int m = n, x, y;
    rep(i, 1, k) {
      read(x, y);
      if (x == y)
        m--; // One independent row/column used up (symmetric move)
      else
        m -= 2; // Two independent rows/columns used up (asymmetric move)
    }
    printf("%d\n", DP(m));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/