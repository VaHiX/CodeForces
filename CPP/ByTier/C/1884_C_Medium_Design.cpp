// Problem: CF 1884 C - Medium Design
// https://codeforces.com/contest/1884/problem/C

/*
Algorithm: Sweep line with coordinate compression
Time Complexity: O(N * log N)
Space Complexity: O(N)

This solution uses coordinate compression and a sweep line approach to find the maximum cost
of selecting a subset of segments. The key idea is to:
1. Compress coordinates of segment endpoints
2. Use a sweep line to process events (segment starts and ends)
3. Track how many segments cover each compressed coordinate
4. For each valid range, compute the difference between maximum and minimum coverage
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

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
int N, M, t, a[MAX_N];
pii seg[MAX_N];
vector<pii> s[MAX_N];
void solve() {
  cin >> N >> M;
  t = 0;
  for (int i = 1; i <= N; i++) {
    int l, r;
    cin >> l >> r;
    a[++t] = l;
    a[++t] = r + 1;
    seg[i] = {l, r + 1};
  }
  sort(a + 1, a + t + 1);
  t = unique(a + 1, a + t + 1) - a - 1;
  sort(seg + 1, seg + N + 1);
  for (int i = 1; i <= N; i++) {
    seg[i].first = lower_bound(a + 1, a + t + 1, seg[i].first) - a;
    seg[i].second = lower_bound(a + 1, a + t + 1, seg[i].second) - a;
  }
  for (int i = 1; i <= t; i++)
    s[i].clear();
  int cnt1 = 0, cntm = 0, cnt = 0, ans = 0;
  for (int i = 1, j = 1; i <= t; i++) {
    for (auto [l, r] : s[i]) {
      cnt--;
      if (a[l] == 1)
        cnt1--;
      if (a[r] == M + 1)
        cntm--;
    }
    for (; j <= N && seg[j].first <= i; j++) {
      cnt++;
      if (a[seg[j].first] == 1)
        cnt1++;
      if (a[seg[j].second] == M + 1)
        cntm++;
      s[seg[j].second].push_back(seg[j]);
    }
    ans = max(ans, cnt - min(cnt1, cntm));
  }
  cout << ans << endl;
}
int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/