// Problem: CF 1864 F - Exotic Queries
// https://codeforces.com/contest/1864/problem/F

// Problem: F. Exotic Queries
// Algorithm: Segment Tree + Binary Indexed Tree + Sweep Line
// Time Complexity: O(n * log(n) + q * log(n))
// Space Complexity: O(n)

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
using u32 = unsigned;
struct IO_Tp {
  const static int _I_Buffer_Size = 53 << 20;
  char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;
  const static int _O_Buffer_Size = 33 << 20;
  char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;
  u32 m[10000];
  IO_Tp() {
    constexpr u32 e0 = '\0\0\0\1', e1 = '\0\0\1\0', e2 = '\0\1\0\0',
                  e3 = '\1\0\0\0';
    int x = 0;
    for (u32 i = 0, c0 = '0000'; i != 10; ++i, c0 += e0)
      for (u32 j = 0, c1 = c0; j != 10; ++j, c1 += e1)
        for (u32 k = 0, c2 = c1; k != 10; ++k, c2 += e2)
          for (u32 l = 0, c3 = c2; l != 10; ++l, c3 += e3)
            m[x++] = c3;
    fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
  }
  ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }
  IO_Tp &operator>>(int &res) {
    bool rev = 0;
    while (!isdigit(*_I_pos) && *_I_pos != '-')
      ++_I_pos;
    if (*_I_pos == '-')
      rev = 1, ++_I_pos;
    res = *_I_pos++ - '0';
    while (isdigit(*_I_pos))
      res = res * 10 + (*_I_pos++ - '0');
    if (rev)
      res = -res;
    return *this;
  }
  IO_Tp &operator<<(int x) {
    if (x == 0) {
      *_O_pos++ = '0';
      return *this;
    }
    static char _buf[35];
    char *_pos = _buf + 35;
    while (x >= 10000)
      *--reinterpret_cast<u32 *&>(_pos) = m[x % 10000], x /= 10000;
    *--reinterpret_cast<u32 *&>(_pos) = m[x];
    _pos += (x < 1000) + (x < 100) + (x < 10);
    _O_pos = copy(_pos, _buf + 35, _O_pos);
    return *this;
  }
  IO_Tp &operator<<(char ch) {
    *_O_pos++ = ch;
    return *this;
  }
} IO;
#define cin IO
#define cout IO
const int N = 1e6 + 10;
int n, q, a[N];
vector<int> pos[N];
struct BIT {
#define lowbit(x) ((x) & (-(x)))
  int b[N];
  void update(int x, int v) {
    x = n - x + 1;
    for (; x <= n; x += lowbit(x))
      b[x] += v;
  }
  int query(int x) {
    x = n - x + 1;
    int sum = 0;
    for (; x > 0; x -= lowbit(x))
      sum += b[x];
    return sum;
  }
} bt;
#define max(x, y) ((x) < (y) ? (y) : (x))
struct ZkwSeg {
  int n, t[N << 2];
  void init(int _n) { n = 1 << __lg(_n) + 1; }
  void update(int p, int v) {
    t[p += n] = v;
    for (p >>= 1; p; p >>= 1)
      t[p] = max(t[p << 1], t[p << 1 | 1]);
  }
  int query(int l, int r) {
    if (l > r)
      return 0;
    int ans = 0;
    for (l += n - 1, r += n + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
      if (~l & 1)
        ans = max(ans, t[l ^ 1]);
      if (r & 1)
        ans = max(ans, t[r ^ 1]);
    }
    return ans;
  }
} sg;
struct Qry {
  int l, r, id;
} qr[N];
int ans[N];
int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i], pos[a[i]].push_back(i);
  for (int i = 1; i <= q; i++)
    cin >> qr[i].l >> qr[i].r, qr[i].id = i;
  sort(qr + 1, qr + q + 1,
       [](const Qry &a, const Qry &b) { return a.r < b.r; });
  sg.init(n);
  for (int i = 1, j = 1; i <= n; i++) {
    int pre = -1;
    for (auto p : pos[i]) {
      sg.update(p, i); // Update the segment tree with current element's position
      if (pre == -1)
        bt.update(i, 1); // First element, update BIT 
      else {
        int v = sg.query(pre + 1, p - 1);  // Query max depth in range [pre+1, p-1]
        if (v)
          bt.update(v, 1);  // If found depth, update BIT
      }
      pre = p;
    }
    for (; j <= q && qr[j].r == i; j++)
      ans[qr[j].id] = bt.query(qr[j].l);  // Answer the query using BIT 
  }
  for (int i = 1; i <= q; i++)
    cout << ans[i] << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/