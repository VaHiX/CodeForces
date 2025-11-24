// Problem: CF 1872 E - Data Structures Fan
// https://codeforces.com/contest/1872/problem/E

/*
 * Code Purpose: Efficiently handle two types of queries on an array and a binary string:
 *   1. Flip bits in a range of the binary string
 *   2. Compute XOR of array elements where the corresponding binary string bit is 1 or 0
 *
 * Algorithms/Techniques:
 *   - Prefix XOR technique for fast range XOR updates
 *   - Lazy flipping using a single variable to track current XOR result
 *   - Bit manipulation for efficient XOR operations
 * 
 * Time Complexity: O(n + q) per test case, where n is array length and q is number of queries.
 * Space Complexity: O(n) for prefix array and string storage.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
namespace IO {
const int S = (1 << 21) + 1;
char ibuf[S], *iS, *iT, obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[55];
int f, qr;
#define gc()                                                                   \
  (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, S, stdin),                    \
               (iS == iT ? EOF : *iS++))                                       \
            : *iS++)
void fl() { fwrite(obuf, 1, oS - obuf, stdout), oS = obuf; }
bool rd(char &x) {
  while (isspace(x = gc())) {
  }
  return x != EOF;
}
bool rd(string &x) {
  while (isspace(c = gc())) {
  }
  if (c == EOF)
    return 0;
  x = c;
  while (!isspace(c = gc()))
    x += c;
  return 1;
}
template <class A> bool rd(A &x) {
  for (f = 1, c = gc(); !isdigit(c); c = gc())
    if (c == '-')
      f = -1;
    else if (c == EOF)
      return 0;
  for (x = 0; isdigit(c); c = gc())
    x = x * 10 + (c & 15);
  x *= f;
  return 1;
}
template <class A, class... B> bool rd(A &x, B &...y) {
  return rd(x) && rd(y...);
}
void wt(char c) {
  *oS++ = c;
  if (oS == oT)
    fl();
}
void wt(const char *x) {
  while (*x)
    wt(*x++);
}
void wt(const string &x) {
  for (char c : x)
    wt(c);
}
template <class A> void wt(A x) {
  if (!x)
    wt('0');
  if (x < 0)
    wt('-'), x = -x;
  while (x)
    qu[++qr] = x % 10 + '0', x /= 10;
  while (qr)
    wt(qu[qr--]);
}
template <class A, class... B> void wt(const A &x, const B &...y) {
  wt(x), wt(y...);
}
struct F {
  ~F() { fl(); }
} f_;
} // namespace IO
using IO::rd;
using IO::wt;
long long sum(long long n) { return n * (n + 1) / 2; }
long long sum(long long l, long long r) { return sum(r) - sum(l - 1); }
void solve() {
  int n;
  rd(n);
  vector<int> a(n);
  for (int &x : a)
    rd(x);
  // Build prefix XOR array for efficient segment queries
  vector<int> pf(n + 1);
  for (int i = 0; i < n; i++)
    pf[i + 1] = pf[i] ^ a[i];
  string s;
  rd(s);
  // Compute initial answer based on positions where s[i] == '1'
  int ans = 0;
  for (int i = 0; i < n; i++)
    if (s[i] == '1')
      ans ^= a[i];
  int q;
  rd(q);
  while (q--) {
    int t;
    rd(t);
    if (t == 1) {
      // Type 1 query: flip bits in range [l,r]
      int l, r;
      rd(l, r), l--, r--;
      // XOR the segment from prefix array to maintain correct answer
      ans ^= pf[r + 1] ^ pf[l];
    } else {
      // Type 2 query: output XOR of elements where s[i] == g
      int g;
      rd(g);
      // If g == 1, we use the current ans directly
      // If g == 0, the result is pf[n] XOR ans (elements where s[i] == 0)
      wt(g == 1 ? ans : (pf[n] ^ ans), ' ');
    }
  }
  wt('\n');
}
int main() {
  int T;
  rd(T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/