// Problem: CF 2132 G - Famous Choreographer
// https://codeforces.com/contest/2132/problem/G

/*
G. Famous Choreographer
Algorithm: Rolling Hash + Brute Force + Symmetry Check
Time Complexity: O(n * m * sqrt(n * m)) per test case
Space Complexity: O(n * m) for hash tables and precomputed powers

The problem is about finding the minimum number of additional ballerinas needed to form a symmetric arrangement under 180-degree rotation.
The approach uses rolling hash techniques to efficiently check if a rectangular region is symmetric with respect to 180-degree rotation. 
We iterate over all possible rectangles in the original grid that could be considered as the top-left portion and verify if they satisfy the symmetry requirement when mirrored.
Finally, we compute how many extra ballerinas are needed based on the area difference.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define int long long
#define lowbit(x) ((x) & (-x))
#define fs first
#define sc second
#define PII pair<int, int>
#define AY3 array<int, 3>
#define comp complex<double>
#define ull unsigned long long
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 5;
const ll inf = 1e18;
const ll MOD = 1e9 + 7;
const double eps = 1e-10;
const double pi = acos(-1);
const ull base0 = 911382323, base1 = 972663749;
ull bsm0[MAXN], bsm1[MAXN];
string s[MAXN];

// Check symmetry for one hash type
bool check(int x0, int y0, int x1, int y1, vector<vector<ull>> &h,
           vector<vector<ull>> &g) {
  int r = x1 - x0 + 1, c = y1 - y0 + 1;
  // Using prefix hashes in both directions to verify symmetrical regions
  return h[x1][y1] - h[x0 - 1][y1] * bsm1[r] - h[x1][y0 - 1] * bsm0[c] +
             h[x0 - 1][y0 - 1] * bsm0[c] * bsm1[r] ==
         g[x0][y0] - g[x1 + 1][y0] * bsm1[r] - g[x0][y1 + 1] * bsm0[c] +
             g[x1 + 1][y1 + 1] * bsm0[c] * bsm1[r];
}

// Second hash type check
const ull base2 = 131, base3 = 13331;
ull bsm2[MAXN], bsm3[MAXN];
bool check1(int x0, int y0, int x1, int y1, vector<vector<ull>> &h1,
            vector<vector<ull>> &g1) {
  int r = x1 - x0 + 1, c = y1 - y0 + 1;
  // Second rolling hash check for double verification
  return h1[x1][y1] - h1[x0 - 1][y1] * bsm3[r] - h1[x1][y0 - 1] * bsm2[c] +
             h1[x0 - 1][y0 - 1] * bsm2[c] * bsm3[r] ==
         g1[x0][y0] - g1[x1 + 1][y0] * bsm3[r] - g1[x0][y1 + 1] * bsm2[c] +
             g1[x1 + 1][y1 + 1] * bsm2[c] * bsm3[r];
}

void solve(int Count_T) {
  int n, m;
  cin >> n >> m;
  // Initialize hash tables for both directions
  vector<vector<ull>> h(n + 2, vector<ull>(m + 2)), g(h), h1(h), g1(h);
  for (int i = 0; i < n; i++)
    cin >> s[i];
  
  // Build forward prefix hashes for main direction
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      h[i][j] = (ull)s[i - 1][j - 1] + h[i][j - 1] * base0 +
                h[i - 1][j] * base1 - h[i - 1][j - 1] * base0 * base1;
  
  // Build backward prefix hashes for reverse direction
  for (int i = n; i; i--)
    for (int j = m; j; j--)
      g[i][j] = (ull)s[i - 1][j - 1] + g[i][j + 1] * base0 +
                g[i + 1][j] * base1 - g[i + 1][j + 1] * base0 * base1;
  
  // Second hash for second check
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      h1[i][j] = (ull)s[i - 1][j - 1] + h1[i][j - 1] * base2 +
                 h1[i - 1][j] * base3 - h1[i - 1][j - 1] * base2 * base3;

  // Third hash for reverse direction
  for (int i = n; i; i--)
    for (int j = m; j; j--)
      g1[i][j] = (ull)s[i - 1][j - 1] + g1[i][j + 1] * base2 +
                 g1[i + 1][j] * base3 - g1[i + 1][j + 1] * base2 * base3;
  
  int ans = inf;
  
  // For all possible rectangles in the original grid that can form a symmetric region
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (check(1, 1, i, j, h, g) && check1(1, 1, i, j, h1, g1))
        ans = min(ans, (2 * n - i) * (2 * m - j) - n * m); // Case: top-left
      if (check(1, j, i, m, h, g) && check1(1, j, i, m, h1, g1))
        ans = min(ans, (2 * n - i) * (m + j - 1) - n * m); // Case: top-right
      if (check(i, 1, n, j, h, g) && check1(i, 1, n, j, h1, g1))
        ans = min(ans, (n + i - 1) * (2 * m - j) - n * m); // Case: bottom-left
      if (check(i, j, n, m, h, g) && check1(i, j, n, m, h1, g1))
        ans = min(ans, (n + i - 1) * (m + j - 1) - n * m); // Case: bottom-right
    }

  cout << ans << "\n";
}

// Precompute hash powers once to avoid recomputation
void precompute() {
  bsm0[0] = bsm1[0] = bsm2[0] = bsm3[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    bsm0[i] = bsm0[i - 1] * base0;
    bsm1[i] = bsm1[i - 1] * base1;
    bsm2[i] = bsm2[i - 1] * base2;
    bsm3[i] = bsm3[i - 1] * base3;
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  precompute();
  int t; cin >> t;
  while (t--) solve(0);
  return 0;
}


// https://github.com/VaHiX/CodeForces/