// Problem: CF 1884 D - Counting Rhyme
// https://codeforces.com/contest/1884/problem/D

/*
Algorithm: Sieve of Eratosthenes with Möbius function for inclusion-exclusion principle
Time Complexity: O(N log log N + N) per test case, where N is the maximum value in the array
Space Complexity: O(N) for the arrays used

This implementation uses the Möbius function and inclusion-exclusion principle to efficiently count the number of "good pairs".
A good pair (i,j) means there's no element k such that both a[i] and a[j] are divisible by a[k].
The algorithm processes all divisors and uses the Möbius function to count valid pairs.
*/
#include <stdio.h>
#include <string.h>
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
int pri[MAX_N], pcnt;
char np[MAX_N], mu[MAX_N];
void init();
int N, a[MAX_N], b[MAX_N];
char mark[MAX_N];
void solve() {
  cin >> N;
  memset(mark, 0, N + 1);
  memset(b, 0, sizeof(int) * (N + 1));
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    b[a[i]]++;
  }
  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    if (b[i]) {
      // Mark all multiples of i as visited
      for (int j = i; j <= N; j += i)
        mark[j] = 1;
      continue;
    }
    if (mark[i])
      continue;
    // For each divisor d, compute sum of elements with multiples of i
    for (int d = 1, j = i; j <= N; d++, j += i) {
      ll sum = 0;
      for (int k = j; k <= N; k += j)
        sum += b[k];
      ans += sum * sum * mu[d];
    }
  }
  cout << ans / 2 << endl;
}
int main() {
  init();
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}
void init() {
  mu[1] = 1;
  for (int i = 2; i < MAX_N; i++) {
    if (!np[i]) {
      pri[++pcnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= pcnt && i * pri[j] < MAX_N; j++) {
      np[i * pri[j]] = 1;
      if (i % pri[j] == 0)
        break;
      mu[i * pri[j]] = -mu[i];
    }
  }
}


// https://github.com/VaHiX/CodeForces/