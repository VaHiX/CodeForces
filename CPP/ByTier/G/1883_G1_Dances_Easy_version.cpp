// Problem: CF 1883 G1 - Dances (Easy version)
// https://codeforces.com/contest/1883/problem/G1

/*
Algorithm: Binary search on the answer.
For each possible number of elements k (from 0 to n), we check if it's possible to make the first k elements of a less than the first k elements of b.
To do this efficiently, we sort both arrays and then try to match a[i] with b[i] in a way that satisfies a[i] < b[i].
We perform binary search on the number of elements k that we can successfully match.
Time Complexity: O(n * log(n) * log(n)) where n is the size of arrays.
Space Complexity: O(n) for storing arrays and auxiliary space.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

#define rep(i, f, t) for (int i(f); i <= t; ++i)
#define re(i, t) for (int i(1); i <= t; ++i)
#define per(i, t, f) for (int i(t); i >= f; --i)
#define pe(i, t) for (int i(t); i >= 1; --i)
#define nx(i, u) for (int i(head[u]); i; i = e[i].nxt)
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r))
#define ls (ix(l, mid))
#define rs (ix(mid + 1, r))
#define mp(i, j) (make_pair(i, j))
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define eps 1e-10
#define look_memory cerr << abs(&sT - &eD) / 1024.0 / 1024 << '\n'
bool sT;
namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
inline char gc() {
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
template <class I> inline void read(I &x) {
  x = 0;
  I f = 1;
  char c = gc();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = -1;
    c = gc();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = gc();
  }
  x *= f;
}
template <class I> inline void write(I x) {
  if (x == 0) {
    putchar('0');
    return;
  }
  I tmp = x > 0 ? x : -x;
  if (x < 0)
    putchar('-');
  int cnt = 0;
  while (tmp > 0) {
    buf1[cnt++] = tmp % 10 + '0';
    tmp /= 10;
  }
  while (cnt > 0)
    putchar(buf1[--cnt]);
}
#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
} // namespace IO
using namespace IO;
const int N = 2e5 + 5;
int T, n, m;
int a[N], b[N];
bool check(int lim) {
  re(i, n - lim) {
    if (a[i] >= b[lim + i])
      return 0;
  }
  return 1;
}
int main() {
  read(T);
  while (T--) {
    read(n), read(m);
    rep(i, 2, n) read(a[i]);
    a[1] = 1; // Assigning a[1] as 1 as per problem statement
    re(i, n) read(b[i]);
    sort(a + 1, a + n + 1); // Sort array a
    sort(b + 1, b + n + 1); // Sort array b
    int l = 0, r = n; // Binary search bounds
    while (l <= r) {
      int mid = (l + r) >> 1; // Midpoint of search range
      if (check(mid)) // Check if we can form valid pairs with 'mid' elements
        r = mid - 1;
      else
        l = mid + 1;
    }
    outn(l); // Output the minimum operations needed
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/