// Problem: CF 1993 D - Med-imize
// https://codeforces.com/contest/1993/problem/D

/*
 * Problem: D. Med-imize
 * Purpose: Given an array and a window size k, we can remove a subarray of size k
 *          until only k elements remain. Goal: find the maximum possible median
 *          of remaining elements.
 *
 * Approach:
 *  - Use binary search on the answer (median value).
 *  - For a given median value d, check if it's possible to achieve this median
 *    by dynamic programming.
 *  - dp[i][0] = minimum number of elements < d among the last i elements,
 *                where the i-th element is not removed from a subarray of size k.
 *  - dp[i][1] = minimum number of elements < d among the last i elements,
 *                where the i-th element is removed from a subarray of size k.
 *  - Transition logic is based on sliding window of size k.
 *
 * Time Complexity: O(n * log(max_val)) where max_val <= 1e9
 * Space Complexity: O(n)
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <utility>

#define pbk push_back
#pragma GCC optimize("Ofast")
typedef long long ll;
namespace Cirno_loves_Reimu {
char buf[1 << 20], obuf[1 << 20], *p1, *p2, *p3 = obuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? 0                                                                     \
       : *p1++)
#define putchar(x)                                                             \
  (p3 - obuf < 1000000)                                                        \
      ? (*p3++ = x)                                                            \
      : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = x)
inline int read() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  while (!isdigit(c) && c != '-')
    c = getchar();
  if (c == '-')
    f = 1, c = getchar();
  while (isdigit(c))
    x = x * 10 + c - '0', c = getchar();
  return f ? -x : x;
}
void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  static char buf[19];
  static int len = -1;
  do
    buf[++len] = x % 10 + 48, x /= 10;
  while (x);
  while (len >= 0)
    putchar(buf[len]), --len;
  putchar(' ');
}
void flush() { fwrite(obuf, p3 - obuf, 1, stdout), exit(0); }
} // namespace Cirno_loves_Reimu
using namespace Cirno_loves_Reimu;
#define FOR(i, a, b) for (int i = a, i##i = b; i <= i##i; ++i)
#define ROF(i, a, b) for (int i = a, i##i = b; i >= i##i; --i)
using namespace std;
typedef pair<int, int> pii;
const int N = 5e5 + 7, inf = 1e9 + 7;
int n, k, lm, a[N], dp[N][2];

// Function to check if median value 'd' is achievable
int chk(int d) {
  dp[0][0] = 0;
  dp[0][1] = inf;
  FOR(i, 1, n) {
    // Get minimum from previous state
    int g = min(dp[i - 1][0], dp[i - 1][1]);
    // Calculate cost if current element is not removed
    dp[i][0] = inf;
    dp[i][1] = g + (a[i] < d); // increment if element < d
    if (i >= k) {
      // If we can make a subarray of size k, update based on sliding window
      FOR(j, 0, 1) dp[i][j] = min(dp[i][j], dp[i - k][j]);
    }
  }
  // Return if it's possible to get at most `lm` elements < d in final array
  return dp[n][1] <= lm;
}

void work() {
  n = read(), k = read();
  FOR(i, 1, n) a[i] = read();
  // Determine how many elements will remain (based on modulo)
  int sr = (n - 1) % k + 1;
  // The required number of elements less than median in the final array
  lm = (sr - 1) / 2;

  int l = 0, r = 1e9 + 7;
  // Binary search on the median value
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (chk(mid))
      l = mid;
    else
      r = mid;
  }
  printf("%d\n", l);
}

signed main() {
  int T = 1;
  T = read();
  while (T--)
    work();
  flush();
  return 0;
}


// https://github.com/VaHiX/CodeForces/