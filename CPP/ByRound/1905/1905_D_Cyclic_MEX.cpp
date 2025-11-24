// Problem: CF 1905 D - Cyclic MEX
// https://codeforces.com/contest/1905/problem/D

/*
Algorithm: Cyclic MEX Maximum Cost
Approach:
1. The problem requires finding the maximum cost among all cyclic shifts of the permutation.
   Cost = sum of mex values for prefixes.
2. We start by identifying a shift where 0 is at the first position to simplify processing.
3. We compute mex values for the prefix array and store them.
4. Using a sliding window technique and a stack-like structure to maintain intervals and their mex values.
5. For each cyclic shift, we update the sum by removing outdated mex values and adding new ones.
6. We track and update the maximum sum encountered during all shifts.

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>

template <class T> inline int qlog(T a) {
  double x = a;
  return ((*(long long *)&x) >> 52 & 2047) - 1023;
}
#define cin Mizuhashi
#define cout Parsee
#define endl '\n'
class Reader {
private:
  static const int BUF_SIZE = 1 << 22;
  char BUF_R[BUF_SIZE], *csy1, *csy2;
#ifndef _LOCAL_RUNNING
#define GC                                                                     \
  (csy1 == csy2 && (csy2 = (csy1 = BUF_R) + fread(BUF_R, 1, BUF_SIZE, stdin),  \
                    csy1 == csy2)                                              \
       ? EOF                                                                   \
       : *csy1++)
#else
  char cur;
#define GC (cur = getchar())
#endif
#define IL inline
public:
  IL bool eof() {
#ifndef _LOCAL_RUNNING
    return csy1 == csy2 &&
           (csy2 = (csy1 = BUF_R) + fread(BUF_R, 1, BUF_SIZE, stdin),
            csy1 == csy2);
#else
    return cur == EOF;
#endif
  }
  template <class Ty> IL Reader &operator>>(Ty &t) {
    int u = 0;
    char c = GC;
    for (t = 0; c < 48 || c > 57; c = GC)
      if (c == EOF)
        break;
      else if (c == '-')
        u = 1;
    for (; c > 47 && c < 58; c = GC)
      t = (t << 1) + (t << 3) + (c ^ 48);
    t = u ? -t : t;
    return *this;
  }
  IL Reader &operator>>(double &t) {
    int tmp, u = 0;
    char c = GC;
    for (tmp = 0; c < 48 || c > 57; c = GC)
      if (c == EOF)
        break;
      else if (c == '-')
        u = 1;
    for (; c > 47 && c < 58; c = GC)
      tmp = (tmp << 1) + (tmp << 3) + (c ^ 48);
    t = (tmp = u ? -tmp : tmp);
    if (c == '.') {
      double x = 1;
      for (c = GC; c > 47 && c < 58; c = GC)
        t += (x /= 10) * (c ^ 48);
    }
    return *this;
  }
  IL Reader &operator>>(char *s) {
    char c = GC;
    for (*s = 0; c < 33; c = GC)
      if (c == EOF)
        return *this;
    for (; c > 32; c = GC)
      *s++ = c;
    *s = 0;
    return *this;
  }
  IL Reader &operator>>(char &c) {
    for (c = GC; c < 33; c = GC)
      if (c == EOF)
        return *this;
    return *this;
  }
} cin;
class Writer {
private:
  static const int BUF_SIZE = 1 << 22;
  char BUF_W[BUF_SIZE], *csy;
#define IL inline
  inline void WC(const char c) {
    if (csy - BUF_W == BUF_SIZE)
      fwrite(BUF_W, 1, BUF_SIZE, stdout), csy = BUF_W;
    *csy++ = c;
  }

public:
  Writer() : csy(BUF_W) {}
  ~Writer() { fwrite(BUF_W, 1, csy - BUF_W, stdout); }
  IL void flush() {
    fwrite(BUF_W, 1, csy - BUF_W, stdout);
    csy = BUF_W;
  }
  template <class Ty> IL Writer &operator<<(Ty x) {
    static int sta[32], top;
    if (x < 0) {
      WC('-');
      do
        sta[top++] = -(x % 10);
      while (x /= 10);
    } else
      do
        sta[top++] = x % 10;
      while (x /= 10);
    while (top)
      WC(sta[--top] ^ 48);
    return *this;
  }
  IL Writer &operator<<(const char &c) {
    WC(c);
    return *this;
  }
  IL Writer &operator<<(const char *s) {
    while (*s)
      WC(*s++);
    return *this;
  }
  IL Writer &operator<<(char *s) {
    while (*s)
      WC(*s++);
    return *this;
  }
} cout;
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAX_N = 1000000 + 5;
const int MAX_M = 1 << 22;
const int INF32 = 0x3f3f3f3f;
int N, a[MAX_N], b[MAX_N], mex[MAX_N];
char vis[MAX_N];
struct Node {
  int val, l, r;
  inline bool operator<(const Node &comp) const { return val < comp.val; }
} sta[MAX_N << 2];
void solve() {
  cin >> N;
  ll ans = 0, sum = 0;
  int pos0 = 0;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    if (!a[i])
      pos0 = i;
  }
  for (int i = pos0; i <= N; i++)
    b[i - pos0 + 1] = a[i];
  for (int i = 1; i < pos0; i++)
    b[i + N - pos0 + 1] = a[i];
  for (int i = 1; i <= N; i++)
    a[i] = b[i];
  for (int i = 1; i <= N; i++) {
    mex[i] = mex[i - 1];
    vis[a[i]] = 1;
    while (vis[mex[i]])
      mex[i]++;
    sum += mex[i];
  }
  int tp = 0, hd = 1;
  for (int i = 1, j; i <= N; i = j) {
    for (j = i; j <= N && mex[i] == mex[j]; j++)
      ;
    sta[++tp] = (Node){mex[i], i, j - 1};
  }
  ans = sum;
  for (int i = 1; i < N; i++) {
    int tot = 0;
    sum -= sta[hd].val;
    if (sta[hd].l == sta[hd].r)
      hd++;
    else {
      sta[hd].l++;
    }
    while (tp >= hd && sta[tp].val >= a[i]) {
      int len = sta[tp].r - sta[tp].l + 1;
      tot += len;
      sum -= 1ll * len * sta[tp].val;
      tp--;
    }
    if (tp < hd) {
      sta[++tp] = (Node){0, i + 1, N + i - 1};
      sta[++tp] = (Node){mex[N], N + i, N + i};
      sum = mex[N];
    } else {
      sum += 1ll * a[i] * tot + mex[N];
      if (sta[tp].val == a[i]) {
        sta[tp].r = N + i - 1;
      } else {
        sta[tp + 1] = (Node){a[i], sta[tp].r + 1, N + i - 1};
        tp++;
      }
      if (sta[tp].val == mex[N])
        sta[tp].r++;
      else
        sta[++tp] = (Node){mex[N], N + i, N + i};
    }
    ans = max(ans, sum);
  }
  cout << ans << endl;
  memset(vis, 0, N);
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/