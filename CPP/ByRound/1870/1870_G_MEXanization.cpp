// Problem: CF 1870 G - MEXanization
// https://codeforces.com/contest/1870/problem/G

/*
Algorithm: MEXanization Problem
Purpose: For each prefix of the array, compute the maximum possible MEX (minimum excluded) that can be obtained 
         after performing a series of operations on the multiset formed by the prefix.
Techniques: 
- Segment Tree for maintaining frequency of elements in current prefix
- Binary search on answer combined with greedy logic to check validity
- Efficiently updating and querying multiset properties

Time Complexity: O(n * log(n) * log(n)) per test case, where n is the length of the array
Space Complexity: O(n) for arrays and segment tree storage

Operations:
1. Maintain a segment tree to count frequency of each element.
2. For each prefix, greedily try to build up the MEX from 0 onwards.
3. Use binary search to find the maximum valid MEX.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>

#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
using namespace std;
int plen, ptop, pstk[40];
char rdc[1 << 14], wtc[1 << 23], *rS, *rT;
#define gc()                                                                   \
  (rS == rT                 ? rT = (rS = rdc) + fread(rdc, 1, 1 << 14, stdin), \
   (rS == rT ? EOF : *rS++) : *rS++)
#define pc(x) wtc[plen++] = (x)
#define flush() fwrite(wtc, 1, plen, stdout), plen = 0
template <class T = int> inline T read() {
  T x = 0;
  char ch;
  bool f = 1;
  while (!isdigit(ch = gc()))
    if (ch == '-')
      f ^= 1;
  do
    x = (x << 1) + (x << 3) + (ch ^ 48);
  while (isdigit(ch = gc()));
  return f ? x : -x;
}
inline int read(char *const s) {
  char *t = s, ch;
  while (!isgraph(ch = gc()))
    ;
  do
    (*(t++)) = ch;
  while (isgraph(ch = gc()));
  return (*t) = 0, t - s;
}
template <class T = int> inline void write(T x) {
  if (plen >= 8000000)
    flush();
  if (!x)
    return pc('0'), void();
  if (x < 0)
    pc('-'), x = -x;
  for (; x; x /= 10)
    pstk[++ptop] = x % 10;
  while (ptop)
    pc(pstk[ptop--] + '0');
}
inline void write(const char *s) {
  if (plen >= 8000000)
    flush();
  for (int i = 0; *(s + i); pc(*(s + (i++))))
    ;
}
inline void write(char *const s) {
  if (plen >= 8000000)
    flush();
  for (int i = 0; *(s + i); pc(*(s + (i++))))
    ;
}
typedef pair<int, int> PII;
const int N = 2e5 + 5;
int n;
int a[N], b[N], T[N << 2];
inline void upd(int p, int l, int r, int x, int y) {
  if (l == r)
    return T[p] = y, void();
  int mid = (l + r) >> 1;
  if (x <= mid)
    upd(p << 1, l, mid, x, y);
  else
    upd(p << 1 | 1, mid + 1, r, x, y);
  T[p] = min(T[p << 1], T[p << 1 | 1]);
}
inline int find(int p, int l, int r, int x, int y) {
  if (T[p] >= y)
    return -1;
  if (l == r)
    return l;
  int mid = (l + r) >> 1;
  int res = (x > mid ? find(p << 1 | 1, mid + 1, r, x, y) : -1);
  return ~res ? res : find(p << 1, l, mid, x, y);
}
inline bool check(int x, LL y, int s) {
  for (int i = x; i; --i)
    if (b[i] < s)
      if ((y -= (i - 1ll) * (s - b[i])) < 0)
        return 0;
      else
        s += s - b[i];
  return 1;
}
inline bool check(int x, LL y) {
  if ((y -= x) < 0)
    return 0;
  for (int s = 1, p = x - 1; p; s += s - b[p--]) {
    if (p <= 4000)
      return check(p, y, s);
    p = find(1, 1, n + 1, p, s);
    if (p == -1)
      return 1;
    if ((y -= (p - 1ll) * (s - b[p])) < 0)
      return 0;
  }
  return 1;
}
inline void MAIN() {
  n = read();
  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    upd(1, 1, n + 1, a[i], ++b[a[i]]);
    if (i == 1)
      write(max(1, a[i]));
    else {
      for (; check(ans + 1, i); ++ans)
        ;
      write(ans);
    }
    pc(i < n ? ' ' : '\n');
  }
  for (int i = 1; i <= n; ++i)
    upd(1, 1, n + 1, a[i], b[a[i]] = 0);
}
signed main() {
  for (int T = read(); T--; MAIN())
    ;
  return flush();
}


// https://github.com/VaHiX/CodeForces/