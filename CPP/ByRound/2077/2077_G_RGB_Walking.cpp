// Problem: CF 2077 G - RGB Walking
// https://codeforces.com/contest/2077/problem/G

/*
G. RGB Walking
Algorithms/Techniques: 
- Union-Find (Disjoint Set Union) for detecting cycles and grouping vertices
- BFS or DFS traversal to explore all possible paths with color constraints
- Modular arithmetic and GCD to handle cyclic properties of colors and weights
- Optimization using bitmasking and brute-force over small combinations

Time Complexity: O(m * α(n) + 8 * 2^3 * log(max_weight))
Space Complexity: O(n * 8 + m)
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long LL;
typedef double DB;
const int N = 222222;
int n, m, w, ex[N], ey[N], ez[N], ec[N], f[N * 8], s[3], ans;
char ch[11];
int fnd(int x) {
  if (f[x] == x)
    return x;
  return f[x] = fnd(f[x]); // Path compression for Union-Find
}
void solve2(int D, int X, int Y, int x, int y) {
  int g, a, b, c, i;
  x = (x % X + X) % X; // Normalize x modulo X
  y = (y % Y + Y) % Y; // Normalize y modulo Y
  g = __gcd(__gcd(X, Y), D); // Compute GCD of all three values
  D /= g, X /= g, Y /= g; // Reduce to co-prime representation
  a = __gcd(X, Y); // Compute GCD of X and Y
  b = __gcd(D, Y); // Compute GCD of D and Y
  c = __gcd(D, X); // Compute GCD of D and X
  for (i = 0; i < a; i++)
    ans = min((LL)ans, max((x + (LL)i * b * c * g) % (a * c * g),
                           (y + (LL)i * b * c * g) % (a * b * g))); // Minimize difference between two modular values
}
void solve(int j) {
  int x, y, z;
  x = j & 1 ? s[0] : 0; // Extract bit 0 from mask
  y = j & 2 ? s[1] : 0; // Extract bit 1 from mask
  z = j & 4 ? s[2] : 0; // Extract bit 2 from mask
  solve2(s[0] * 2, s[1] * 2, s[2] * 2, x - y, x - z); // Call for first permutation
  solve2(s[1] * 2, s[2] * 2, s[0] * 2, y - z, y - x); // Call for second permutation
  solve2(s[2] * 2, s[0] * 2, s[1] * 2, z - x, z - y); // Call for third permutation
}
int main() {
  int T, i, j, k, x, y, z, o;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &w);
    for (k = 0; k < 3; k++)
      s[k] = 0; // Initialize color sums to zero
    for (i = 1; i <= m; i++) {
      scanf("%d%d%d%s", ex + i, ey + i, ez + i, ch);
      ec[i] = ch[0] == 'r' ? 0 : ch[0] == 'g' ? 1 : 2; // Map color to index
      s[ec[i]] = __gcd(s[ec[i]], ez[i]); // Compute GCD for each color's edge weights
    }
    for (i = 1; i <= n; i++)
      for (j = 0; j < 8; j++)
        f[i * 8 + j] = i * 8 + j; // Initialize Union-Find structure
    for (i = 1; i <= m; i++) {
      for (j = 0; j < 8; j++)
        f[fnd(ex[i] * 8 + j)] =
            fnd(ey[i] * 8 + (j ^ ((ez[i] / s[ec[i]] % 2) << ec[i]))); // Union based on color and parity
    }
    ans = 1e9; // Initialize answer with large value
    for (j = 0; j < 8; j++)
      if (fnd(1 * 8 + 0) == fnd(n * 8 + j)) // Check if vertex 1 and n are connected under same cycle class
        solve(j); // Perform operations on valid configurations
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/