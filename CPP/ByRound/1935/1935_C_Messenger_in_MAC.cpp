// Problem: CF 1935 C - Messenger in MAC
// https://codeforces.com/contest/1935/problem/C

/*
 * Problem: C. Messenger in MAC
 * Algorithm: Dynamic Programming with Sorting
 * Time Complexity: O(n^2), where n is the number of messages
 * Space Complexity: O(n^2) for the DP table f, and O(n) for the array g
 *
 * The approach uses dynamic programming where we sort the messages by their 'b' values.
 * For each message, we calculate the minimum time to form a set of size j ending at this message.
 * The key idea is to maintain `g[j]` as the minimum cost to achieve a set of size j,
 * and use it to compute the cost of extending existing sets.
 *
 * Key variables:
 * - f[i][j]: minimum time to form a set of size j using messages 1..i
 * - g[j]: minimum cost to form a set of size j (used in the computation)
 * - A[i]: array of messages sorted by 'b' value
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long LL;
const int maxn = 2024;
LL n, k;
LL f[maxn][maxn], g[maxn];
struct Node {
  int a, b;
  bool operator<(Node X) const { return b < X.b; }
} A[maxn];
inline int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}
int main() {
  int T = read();
  while (T--) {
    n = read();
    k = read();
    for (int i = 1; i <= n; i++)
      g[i] = 1e18;
    g[0] = 0;
    for (int i = 1; i <= n; i++)
      A[i] = (Node){read(), read()};
    sort(A + 1, A + 1 + n);  // Sort by 'b' values
    int Ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= i; j++) {
        // Compute the cost of forming a set of size j ending with message i
        f[i][j] = A[i].a + A[i].b + g[j - 1];
        if (j == 1)
          f[i][j] -= A[i].b;  // Special case for single message sets
        if (f[i][j] <= k) {
          Ans = max(Ans, j);  // Update maximum set size if valid
        }
      }
      for (int j = 1; j <= i; j++) {
        // Update g[j] with the minimum cost to form a set of size j ending at message i
        g[j] = min(g[j], f[i][j] - A[i].b);
      }
    }
    printf("%d\n", Ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/