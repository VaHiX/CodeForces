// Problem: CF 1905 F - Field Should Not Be Empty
// https://codeforces.com/contest/1905/problem/F

/*
Algorithm: 
- The problem asks for maximizing the number of "good indices" after swapping exactly two elements in a permutation.
- A good index x satisfies: all elements before x are smaller, all elements after x are larger. 
- This means that x is a local maximum in a sense.
- Key observations:
   - Initially compute prefix and suffix arrays to check for potential candidates for good indices.
   - For each element, check if it can be a good index:
     - If pre[i-1][0] < a[i] and suf[i+1][0] > a[i], then it's a good index.
     - Otherwise, we track potential swaps needed to turn non-good indices into good ones using a map.
- Time Complexity: O(n log n) due to sorting operations in map
- Space Complexity: O(n) for arrays and maps
*/
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <map>
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
int N, a[MAX_N], sum[MAX_N], pos[MAX_N];
int pre[MAX_N][2], suf[MAX_N][2];
map<pii, int> cnt;
void solve() {
  cin >> N;
  bool flag = 1;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    pos[a[i]] = i;
    if (a[i] < a[i - 1])
      flag = 0;
  }
  if (flag) {
    cout << N - 2 << endl;
    return;
  }
  suf[N + 1][0] = suf[N + 1][1] = INF32;
  for (int i = 1; i <= N; i++) {
    pre[i][0] = pre[i - 1][0];
    pre[i][1] = pre[i - 1][1];
    if (pre[i][0] < a[i]) {
      pre[i][1] = pre[i][0];
      pre[i][0] = a[i];
    } else if (pre[i][1] < a[i]) {
      pre[i][1] = a[i];
    }
  }
  for (int i = N; i > 0; i--) {
    suf[i][0] = suf[i + 1][0];
    suf[i][1] = suf[i + 1][1];
    if (a[i] < suf[i][0]) {
      suf[i][1] = suf[i][0];
      suf[i][0] = a[i];
    } else if (a[i] < suf[i][1]) {
      suf[i][1] = a[i];
    }
  }
  cnt.clear();
  for (int i = 1; i <= N; i++) {
    sum[i] = sum[i - 1];
    if (pre[i - 1][0] < a[i] && suf[i + 1][0] > a[i])
      sum[i]++;
    else if (pre[i - 1][0] > a[i] && suf[i + 1][0] < a[i] &&
             pre[i - 1][1] < a[i] && suf[i + 1][1] > a[i]) {
      cnt[pair(pre[i - 1][0], suf[i + 1][0])]++;
    } else if (pre[i - 1][0] > a[i] && pre[i - 1][0] < suf[i + 1][0]) {
      cnt[pair(pre[i - 1][0], a[i])]++;
    } else if (suf[i + 1][0] < a[i] && pre[i - 1][0] < suf[i + 1][0]) {
      cnt[pair(a[i], suf[i + 1][0])]++;
    }
  }
  int ans = 0;
  for (auto [opt, val] : cnt) {
    int l = pos[opt.first], r = pos[opt.second];
    assert(l < r);
    ans = max(ans, sum[N] - (sum[r] - sum[l - 1]) + val);
  }
  cout << ans << endl;
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/