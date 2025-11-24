// Problem: CF 2097 B - Baggage Claim
// https://codeforces.com/contest/2097/problem/B

/*
B. Baggage Claim
Purpose: Count the number of ways to restore a path through a grid from given odd-indexed points.
Algorithms/Techniques: Union-Find (Disjoint Set Union), Graph traversal, Dynamic Programming concepts on graphs.
Time Complexity: O(nm α(nm)) where α is the inverse Ackermann function, effectively constant.
Space Complexity: O(nm)

Each test case processes a grid of size n x m and k+1 fixed odd-indexed points.
We use a union-find data structure to group connected components,
counting constraints on edges and nodes based on degree and adjacency.
*/
#include <bits/std_abs.h>
#include <ctype.h>
#include <stdio.h>

using namespace std;
#define int long long
namespace IO {
char buf[1 << 16], *p1 = buf, *p2 = buf, ibuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin)),          \
   p1 == p2 ? EOF : *p1++)
int rd(int x = 0, int f = 1) {
  for (; !isdigit(ibuf); ibuf = getchar())
    if (ibuf == '-')
      f = -1;
  for (; isdigit(ibuf); ibuf = getchar())
    x = x * 10 + (ibuf ^ 48);
  return x * f;
}
int rds(char *s, int n = 0) {
  for (; !isgraph(ibuf); ibuf = getchar())
    if (ibuf == EOF)
      return -1;
  for (; isgraph(ibuf); ibuf = getchar())
    s[n++] = ibuf;
  return s[n] = 0, n;
}
} // namespace IO
using IO::rd;
using IO::rds;
int deg[1000100];       // Degree count in each component
int d2[1000100];        // Count of 2-edge connections (edges between two odd points)
int pa[1000100];        // Parent array for Union-Find
int siz[1000100];       // Size of each component
int sum[1000100];       // Sum of degrees in component
int s2[1000100];        // Sum of d2 in component
int x[1000100], y[1000100];  // Input coordinates

// Find root with path compression
int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

const int mod = 1000000007;  

// Union two sets
void con(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  siz[x] += siz[y];
  pa[y] = x;
}

// Main solution function
int slv(int n, int m, int k) {
  for (int i = 0; i < n * m; i++)
    pa[i] = i, siz[i] = 1, deg[i] = 0, sum[i] = 0, d2[i] = 0, s2[i] = 0;

  // Process all consecutive odd-indexed points to define segments and update counters
  for (int i = 0; i < k; i++) {
    int a = x[i], b = y[i], c = x[i + 1], d = y[i + 1];
    if (abs(a - c) + abs(b - d) != 2)
      return 0; // Not valid adjacent cells

    if (abs(a - c) == 0) {
      // Vertical segment
      int x_coord = a, y_coord = (b + d) >> 1;
      d2[x_coord * m + y_coord]++;
    } else if (abs(b - d) == 0) {
      // Horizontal segment
      int x_coord = (a + c) >> 1, y_coord = b;
      d2[x_coord * m + y_coord]++;
    } else {
      // Diagonal segment - mark corner point and connect ends
      deg[a * m + d]++, deg[c * m + b]++;
      con(a * m + d, c * m + b);
    }
  }

  int ans = 1;
  // Aggregate degree counts by component
  for (int i = 0; i < n * m; i++)
    sum[find(i)] += deg[i];

  // Aggregate d2 counts by component
  for (int i = 0; i < n * m; i++)
    s2[find(i)] += d2[i];

  // Count valid paths per component
  for (int i = 0; i < n * m; i++)
    if (find(i) == i) {
      int x = siz[i];
      if (sum[i] + s2[i] * 2 > siz[i] * 2)
        return 0; // Invalid path
      if (sum[i] == siz[i] * 2) {
        ans = ans * 2 % mod;
      } else {
        if (!s2[i])
          ans = ans * siz[i] % mod;
      }
    }

  return ans;
}

signed main() {
  int T = rd();
  while (T--) {
    int n = rd(), m = rd(), k = rd();
    for (int i = 0; i <= k; i++)
      x[i] = rd() - 1, y[i] = rd() - 1;
    printf("%lld\n", slv(n, m, k));
  }
}


// https://github.com/VaHiX/codeForces/