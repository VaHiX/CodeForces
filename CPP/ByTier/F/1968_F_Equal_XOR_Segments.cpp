// Problem: CF 1968 F - Equal XOR Segments
// https://codeforces.com/contest/1968/problem/F

/*
Problem: Equal XOR Segments
Algorithm: 
- Use prefix XOR to determine if a subarray can be split into segments with equal XOR values.
- For a subarray [l, r] to be interesting, we can split it into k segments where each segment has the same XOR value.
- The key insight is that if we split at positions i and j (with l <= i < j <= r), then 
  XOR of subarray [l, i-1] = XOR of subarray [i, j-1] = XOR of subarray [j, r] 
  This implies: b[i-1] ^ b[l-1] = b[j-1] ^ b[i-1] = b[r] ^ b[j-1]
  Which simplifies to: b[l-1] = b[i-1] = b[j-1] = b[r]
- So, if we precompute the prefix XOR values and store for each value the list of indices where that value occurs,
  we can determine existence of valid split efficiently by binary search.
Time Complexity: O(n log n + q log n) where n is the size of the array and q is the number of queries.
Space Complexity: O(n) for the prefix XOR array and auxiliary arrays.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
namespace FastIO {
const int SIZE = 1 << 22 | 1;
char iBuf[SIZE], *iS, *iT, c, oBuf[SIZE], *oS = oBuf, *oT = oBuf + SIZE;
#define gc()                                                                   \
  (iS == iT                 ? iT = iBuf + fread(iS = iBuf, 1, SIZE, stdin),    \
   (iS == iT ? EOF : *iS++) : *iS++)
template <class I> void read(I &x) {
  for (c = gc(); c < '0' || c > '9';)
    c = gc();
  for (x = 0; c >= '0' && c <= '9'; c = gc())
    x = (x << 3) + (x << 1) + (c & 15);
}
inline void flush() {
  fwrite(oBuf, 1, oS - oBuf, stdout);
  oS = oBuf;
}
inline void putc(char x) {
  *oS++ = x;
  if (oS == oT)
    flush();
}
template <class I> void write(I x) {
  static char qu[55];
  char *tmp = qu;
  do
    *tmp++ = (x % 10) ^ 48;
  while (x /= 10);
  while (tmp-- != qu)
    putc(*tmp);
}
struct flusher {
  ~flusher() { flush(); }
} _;
#undef gc
template <class T, class... Arg> void read(T &x, Arg &...args) {
  read(x);
  read(args...);
}
} // namespace FastIO
using FastIO::putc;
using FastIO::read;
using FastIO::write;
#define fer(i, a, b) for (int i = (a); i <= (b); i++)
#define LL long long
const int Maxn = 2e5 + 10;
int T;
int n, q;
int a[Maxn];
LL b[Maxn], t[Maxn], tot;
vector<int> f[Maxn];
int check(int ql, int qr, LL qx) {
  if (ql > qr || f[qx].empty())
    return -1;
  int l = 1, r = f[qx].size(), mid;
  int ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (f[qx][mid - 1] > qr) {
      r = mid - 1;
    } else {
      if (f[qx][mid - 1] >= ql)
        ans = f[qx][mid - 1];
      l = mid + 1;
    }
  }
  return ans;
}
signed main() {
  read(T);
  while (T--) {
    read(n, q);
    t[0] = 0;
    f[0].clear();
    fer(i, 1, n) {
      read(a[i]);
      b[i] = b[i - 1] ^ a[i];
      t[i] = b[i];
      f[i].clear();
    }
    sort(t, t + n + 1);
    tot = unique(t, t + n + 1) - t;
    fer(i, 1, n) {
      b[i] = lower_bound(t, t + tot, b[i]) - t;
      f[b[i]].push_back(i);
    }
    int l, r;
    while (q--) {
      read(l, r);
      if (b[l - 1] == b[r]) {
        putc('Y'), putc('E'), putc('S'), putc('\n');
        continue;
      }
      if (check(l, check(l, r - 1, b[l - 1]) - 1, b[r]) != -1) {
        putc('Y'), putc('E'), putc('S'), putc('\n');
      } else
        putc('N'), putc('O'), putc('\n');
    }
    putc('\n');
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/