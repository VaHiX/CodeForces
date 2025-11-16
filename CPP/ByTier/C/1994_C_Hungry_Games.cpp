// Problem: CF 1994 C - Hungry Games
// https://codeforces.com/contest/1994/problem/C

/*
Algorithm/Techniques: Two Pointers, Prefix Sums, Sliding Window
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This problem uses a two-pointer technique combined with prefix sums to efficiently
count the number of subarrays whose sum is less than or equal to x. The core idea is:

1. For each starting index i, we find the maximum ending index j such that the subarray
   from i to j has total toxicity <= x.
2. We then use dynamic programming to count how many subarrays starting at each index
   will result in g = 0 (i.e., exceed the limit at any point).
3. The final answer is total subarrays minus those that end up with g=0.

The prefix sum technique helps quickly compute the sum of any subarray.
The sliding window approach avoids redundant computation when finding valid ranges.
*/

#include <ctype.h>
#include <stdio.h>
#include <iostream>
#ifdef ONLINE_JUDGE
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
#endif
using namespace std;
typedef long long ll;
int read() {
  int num = 0, f = 1;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = -1;
  while (isdigit(c))
    num = num * 10 + (c & 15), c = getchar();
  return num * f;
}
void write(ll x, char ch = ' ') {
  int F[20], cnt = 0;
  if (!x)
    putchar('0');
  if (x < 0)
    putchar('-'), x = -x;
  while (x)
    F[cnt++] = x % 10 + '0', x /= 10;
  while (cnt)
    putchar(F[--cnt]);
  putchar(ch);
}
namespace Main {
const int N = 200010;
int n, a[N], x, y, z, xx, yy, zz, nxt[N], f[N];
long long s[N], ans;
void main() {
  n = read(), x = read(), f[n + 1] = -1, ans = n * (n + 1ll) / 2; // Total number of subarrays
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + (a[i] = read()); // Compute prefix sums
  s[n + 1] = s[n] + x + 1; // Sentinel value to handle edge cases
  for (int i = 0, j = 1; i <= n; ++i) {
    for (; j <= n && s[j] - s[i] <= x; ++j) // Find max j for current i where sum <= x
      ;
    nxt[i] = j; // Store next index where condition fails
  }
  for (int i = n; i >= 0; --i)
    f[i] = f[nxt[i]] + 1, ans -= f[i]; // DP to count invalid subarrays
  write(ans, '\n');
}
}; // namespace Main
int main() {
  const bool base = 1, IO = 1;
  int T;
  if (!base)
    T = 1;
  else if (IO)
    T = read();
  else
    ios::sync_with_stdio(0), cin >> T;
  for (; T--;)
    Main::main();
  return 0;
}


// https://github.com/VaHiX/CodeForces/