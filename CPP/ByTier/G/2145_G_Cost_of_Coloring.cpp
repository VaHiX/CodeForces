// Problem: CF 2145 G - Cost of Coloring
// https://codeforces.com/contest/2145/problem/G

/*
G. Cost of Coloring
Algorithms/Techniques: Dynamic Programming, Inclusion-Exclusion Principle, Stirling Numbers of the Second Kind, Binomial Coefficients
Time Complexity: O(n * m * k)
Space Complexity: O(n * m)

This problem uses dynamic programming with inclusion-exclusion principle to count the number of beautiful colorings
with a given minimum number of operations. It calculates the number of valid ways to color a grid such that:
1. All cells are colored.
2. Exactly k colors are used, from 1 to k.
3. The minimal number of operations needed is exactly i.

The approach involves:
- Precomputing Stirling numbers of the second kind S(n, k) which count partitions of n elements into k non-empty subsets.
- Using binomial coefficients to choose which rows/columns to color.
- Applying inclusion-exclusion to ensure all k colors are used.
- The answer is computed for each value from min(n,m) to n+m-1.

The solution handles special cases when k=1 and uses modular arithmetic throughout for large numbers.
*/

#include <stdio.h>
#include <ext/pb_ds/detail/type_utils.hpp>
#include <algorithm>
#include <utility>

#define gt getchar
#define pt putchar
#define fst first
#define scd second
#define SZ(s) ((int)s.size())
#define all(s) s.begin(), s.end()
#define pb push_back
#define eb emplace_back
typedef long long ll;
typedef double db;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;
const int N = 4005;
const int mod = 998244353;
using namespace std;
using namespace __gnu_pbds;
typedef pair<int, int> pii;
template <class T, class I> inline bool chkmax(T &a, I b) {
  return b > a ? a = b, 1 : 0;
}
template <class T, class I> inline bool chkmin(T &a, I b) {
  return b < a ? a = b, 1 : 0;
}
inline bool __(char ch) { return ch >= 48 && ch <= 57; }
template <class T> inline void read(T &x) {
  x = 0;
  bool sgn = 0;
  static char ch = gt();
  while (!__(ch) && ch != EOF)
    sgn |= (ch == '-'), ch = gt();
  while (__(ch))
    x = (x << 1) + (x << 3) + (ch & 15), ch = gt();
  if (sgn)
    x = -x;
}
template <class T, class... I> inline void read(T &x, I &...x1) {
  read(x);
  read(x1...);
}
template <class T> inline void print(T x) {
  static char stk[70];
  short top = 0;
  if (x < 0)
    pt('-');
  do {
    stk[++top] = x >= 0 ? (x % 10 + 48) : (-(x % 10) + 48), x /= 10;
  } while (x);
  while (top)
    pt(stk[top--]);
}
template <class T> inline void printsp(T x) {
  print(x);
  putchar(' ');
}
template <class T> inline void println(T x) {
  print(x);
  putchar('\n');
}
int n, m, k, S[N][N], binom[N][N], ans[N];
inline void add(int &a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
}
inline void del(int &a, int b) {
  a -= b;
  if (a < 0)
    a += mod;
}
signed main() {
  read(n, m, k);
  int fac = 1;
  for (int i = 1; i < k; ++i)
    fac = 1ll * fac * i % mod;
  S[0][0] = binom[0][0] = 1;
  for (int i = 1; i <= 4000; ++i) {
    binom[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      S[i][j] = (1ll * S[i - 1][j] * j + S[i - 1][j - 1]) % mod, // Stirling number recurrence
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod; // Pascal's triangle for binomial coefficients
  }
  for (int i = 0; i < m; ++i)
    for (int j = 1; j <= n; ++j)
      if (j < m - i) // Checking bounds to avoid invalid combinations
        add(ans[n + i], 1ll * binom[n][j] * binom[m][i] % mod * // Multiplying binomial coefficients
                            S[n - j + i][k - 1] % mod * fac % mod); // Using Stirling numbers
  for (int i = 0; i < n; ++i)
    for (int j = 1; j <= m; ++j)
      if (j <= n - i) // Checking bounds to avoid invalid combinations
        add(ans[m + i], 1ll * binom[m][j] * binom[n][i] % mod * // Multiplying binomial coefficients
                            S[m - j + i][k - 1] % mod * fac % mod); // Using Stirling numbers
  if (k == 1) // Special case for k=1, only one valid coloring possible with minimum operations = min(n,m)
    fill(ans + min(n, m), ans + n + m, 0), add(ans[min(n, m)], 1);
  for (int i = min(n, m); i < n + m; ++i)
    printsp(ans[i]);
  printf("\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/