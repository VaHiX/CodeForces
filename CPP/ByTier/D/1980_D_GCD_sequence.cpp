// Problem: CF 1980 D - GCD-sequence
// https://codeforces.com/contest/1980/problem/D

/*
 * Problem: D. GCD-sequence
 * 
 * Algorithm:
 * - For each element in the array, we compute the GCD sequence of neighboring pairs.
 * - We determine if removing exactly one element results in a non-decreasing GCD sequence.
 * 
 * Approach:
 * 1. Precompute the GCD sequence b where b[i] = GCD(a[i], a[i+1]).
 * 2. Create two auxiliary arrays f1 and f2:
 *    - f1[i] indicates whether the prefix b[1..i] is non-decreasing.
 *    - f2[i] indicates whether the suffix b[i..n-1] is non-decreasing.
 * 3. Check if removing the first or last element makes the sequence valid.
 * 4. For removing any middle element a[i], check if the concatenation of valid prefix and suffix with new GCD at position i forms a valid sequence.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>

typedef long long ll;
using namespace std;
#define endl '\n'
#define Endl '\n'
#define itn int
#define mian main
#define L(x, a, b) for (int x = (a); x <= (b); x++)
#define R(x, a, b) for (int x = (a); x >= (b); x--)
namespace IO {
template <class T> T Max(T a, T b) {
  if (a > b)
    return a;
  return b;
}
template <class T> T Min(T a, T b) {
  if (a < b)
    return a;
  return b;
}
static char buf[100000], *pa(buf), *pb(buf);
#define gc                                                                     \
  pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb)       \
      ? EOF                                                                    \
      : *pa++
template <class T> void read(T &x) {
  x = 0;
  T f = 1;
  char ch = gc;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = gc;
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch & 15), ch = gc;
  x *= f;
}
template <typename T, typename... Args> void read(T &nums, Args &...args) {
  read(nums);
  read(args...);
}
template <class T> void write1(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write1(x / 10);
  putchar(x % 10 + '0');
  return;
}
template <class T> void write(T x, char c = ' ') { write1(x), putchar(c); }
} // namespace IO
using namespace IO;
const int N = 2e5 + 10;
int a[N], b[N];
bool f1[N], f2[N];
int main() {
  int t;
  read(t);
  while (t--) {
    int n;
    read(n);
    L(i, 1, n) read(a[i]);
    L(i, 2, n) b[i - 1] = __gcd(a[i], a[i - 1]);
    f1[0] = 1;
    L(i, 1, n - 1)
    if (b[i] >= b[i - 1])
      f1[i] = f1[i - 1];
    else
      f1[i] = 0;
    f2[n + 1] = f2[n] = f2[n - 1] = 1;
    R(i, n - 2, 1)
    if (b[i + 1] >= b[i])
      f2[i] = f2[i + 1];
    else
      f2[i] = 0;
    bool f = f1[n - 2] || f2[2];
    if (f) {
      puts("YES");
      continue;
    }
    b[n] = 1e9;
    L(i, 2, n - 1) {
      int x = __gcd(a[i - 1], a[i + 1]);
      if (f1[i - 2] && f2[i + 1])
        if (b[i - 2] <= x && b[i + 1] >= x) {
          f = 1;
          break;
        }
    }
    if (f)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/