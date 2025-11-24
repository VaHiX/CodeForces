// Problem: CF 1900 F - Local Deletions
// https://codeforces.com/contest/1900/problem/F

/*
Algorithm/Techniques: 
- Preprocessing using segment tree-like approach to simulate f(x) function on subarrays
- For each step of the process, we identify local minima/maxima and build a new array
- Fast input/output using custom buffered I/O
- Efficient querying using precomputed positions and recursive application of operations

Time Complexity: O(N log N + Q) where N is the size of the permutation and Q is number of queries
Space Complexity: O(N log N) to store precomputed arrays and positions

The key idea is to precompute how the function f behaves on all prefixes of the array,
and then use those precomputed results to quickly answer queries.
This reduces the per-query time from O(N) to approximately O(log N) by using
the precomputed structures to skip intermediate steps.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define OJ
namespace Fread {
const int SIZE = 1 << 18;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 17;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef OJ
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
#endif
namespace Fastio {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
      c = getchar();
    while (c >= '0' && c <= '9') {
      x = x * 10 + (c - '0');
      c = getchar();
    }
    return *this;
  }
  Reader() {}
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
    if (x < 0) {
      putchar('-');
      x = -x;
    }
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
  Writer() {}
} cout;
} // namespace Fastio
#define cin Fastio ::cin
#define cout Fastio ::cout
#define vi vector<int>
int main() {
  int N, Q;
  cin >> N >> Q;
  vector<vi> arrs, posi;
  arrs.push_back(vi(N + 1));
  for (int i = 1; i <= N; i++)
    cin >> arrs[0][i];
  for (int sz = N, sgn = 1; sz != 1; sgn *= -1) {
    posi.push_back(vi(sz + 1));
    vi tmp(1, 0);
    for (int i = 1; i <= sz; i++) {
      bool flag = 1;
      if (i != 1 && sgn * (arrs.back()[i] - arrs.back()[i - 1]) > 0)
        flag = 0;
      if (i != sz && sgn * (arrs.back()[i] - arrs.back()[i + 1]) > 0)
        flag = 0;
      if (flag)
        tmp.push_back(arrs.back()[i]);
      posi.back()[i] = posi.back()[i - 1] + flag;
    }
    arrs.push_back(tmp);
    sz = posi.back()[sz];
  }
  auto Calc = [&](vi P, int sgn) {
    while (P.size() != 1) {
      vi C;
      for (int i = 0; i < P.size(); i++) {
        bool flag = 1;
        if (i && sgn * (P[i] - P[i - 1]) > 0)
          flag = 0;
        if (i + 1 < P.size() && sgn * (P[i] - P[i + 1]) > 0)
          flag = 0;
        if (flag)
          C.push_back(P[i]);
      }
      P.swap(C);
      sgn *= -1;
    }
    return P[0];
  };
  while (Q--) {
    int L, R;
    cin >> L >> R;
    int cur = 0, sgn = 1, Lx = -1, Rx = -1;
    while (R - L > 3) {
      int nL = posi[cur][L] + 1, nR = posi[cur][R - 1], nLx = -1, nRx = -1;
      if (sgn * (arrs[cur][L + 1] - arrs[cur][L]) > 0)
        nLx = arrs[cur][L];
      if (sgn * (arrs[cur][R - 1] - arrs[cur][R]) > 0)
        nRx = arrs[cur][R];
      if (Lx == -1 || sgn * (Lx - arrs[cur][L]) > 0)
        Lx = nLx;
      if (Rx == -1 || sgn * (Rx - arrs[cur][R]) > 0)
        Rx = nRx;
      L = nL, R = nR;
      cur++;
      sgn *= -1;
    }
    vi P;
    if (Lx != -1)
      P.push_back(Lx);
    for (int i = L; i <= R; i++)
      P.push_back(arrs[cur][i]);
    if (Rx != -1)
      P.push_back(Rx);
    cout << Calc(P, sgn) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/