// Problem: CF 1898 D - Absolute Beauty
// https://codeforces.com/contest/1898/problem/D

/*
Problem: Maximum Absolute Beauty with at most one swap
Algorithm: 
  - For each element, determine if a[i] < b[i] (c[i] = 1) or a[i] >= b[i] (c[i] = 0)
  - Split the arrays into two groups based on this condition
  - Find the maximum gain by swapping two elements in b to maximize overall absolute difference
  - Time Complexity: O(n)
  - Space Complexity: O(n)

The algorithm works by:
1. Calculating initial sum of absolute differences
2. Classifying elements into two groups based on a[i] vs b[i]
3. For each group, track max and min values
4. Calculate potential improvement from swaps
5. Add twice the improvement to the initial sum (since absolute difference can increase by up to 2 * difference)

*/
#include <stdio.h>
#include <stdlib.h>
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
const int MAX_N = 200000 + 5;
const int INF32 = 0x3f3f3f3f;
int N, a[MAX_N], b[MAX_N];
char c[MAX_N];
void solve() {
  ll ans0 = 0;
  cin >> N;
  for (int i = 1; i <= N; i++)
    cin >> a[i];
  int maxb[2] = {0, 0};
  int minc[2] = {INF32, INF32};
  for (int i = 1; i <= N; i++) {
    cin >> b[i];
    ans0 += abs(a[i] - b[i]);
    if (a[i] < b[i]) {
      c[i] = 1;
      swap(a[i], b[i]); // Swap to make a[i] >= b[i] for consistency
    } else
      c[i] = 0;
    maxb[c[i]] = max(maxb[c[i]], b[i]);  // Track max b value in each group
    minc[c[i]] = min(minc[c[i]], a[i]);  // Track min a value in each group
  }
  int ex = max(max(maxb[0] - minc[0], maxb[1] - minc[1]),
               max(maxb[0] - minc[1], maxb[1] - minc[0]));
  cout << ans0 + 2 * max(ex, 0) << endl;
}
int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/