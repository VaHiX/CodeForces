// Problem: CF 1795 D - Triangle Coloring
// https://codeforces.com/contest/1795/problem/D

/*
 * Problem: Triangle Coloring
 * 
 * Purpose: 
 *   Given an undirected graph with n vertices (n divisible by 6), structured as n/3 triangles
 *   each containing 3 vertices, compute the number of valid 2-colorings (red/blue) such that
 *   exactly n/2 vertices are red and n/2 are blue, that maximize the total edge weight
 *   between differently colored vertices.
 * 
 * Approach:
 *   - Each triangle (3 vertices) can be colored in 3 possible ways to maximize edge weight:
 *     1. All red, all blue => 0 weight edge between colors (not optimal)
 *     2. Two red, one blue or vice versa => 1 edge weight (max for triangle)
 *     3. One red, two blue => 2 edge weights (max for triangle)
 *   - The optimal coloring for a triangle depends on edge weights: we sort the 3 edges
 *     and assign colorings based on how many edges need to be cut to separate red and blue nodes.
 *   - Once the valid configurations per triangle are determined, we compute total number
 *     of valid colorings with max weight using combinatorics:
 *     - Total ways to select n/2 red vertices from n total = C(n, n/2)
 *     - Adjusted for specific constraints in each triangle
 * 
 * Time Complexity: O(n)
 *   - Input parsing: O(n)
 *   - Sorting and assigning color options for n/3 triangles: O(n)
 *   - Computing combinations and final answer: O(n)
 * 
 * Space Complexity: O(n)
 *   - Storage for edge weights and triangle coloring options
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
#define PB push_back
#define PF push_front
#define fir first
#define sec second
#define all(a) begin(a), end(a)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 3e5 + 10, mod = 998244353;
int n;
int c[N];
void change(int &x, int &y, int &z) {
  int mx = max({x, y, z});
  int mi = min({x, y, z});
  int mid = x + y + z - mx - mi;
  x = mx;
  y = mid;
  z = mi;
}
ll qmi(ll a, int b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
int main() {
  scanf("%d", &n);
  n /= 3;
  for (int i = 1; i <= n; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    change(x, y, z); // Sort weights in descending order for processing
    if ((x > y && y > z) || (x == y && y > z))
      c[i] = 1; // Optimal coloring for this triangle contributes 1 way
    else if (x > y && y == z)
      c[i] = 2; // Optimal coloring for this triangle contributes 2 ways
    else
      c[i] = 3; // Optimal coloring for this triangle contributes 3 ways
  }
  ll x = 1, y = 1;
  for (int i = 1; i <= n; i++) {
    if (i <= n / 2) // Factorial calculation for combination denominator
      y = y * i % mod;
    x = x * i % mod; // Full factorial numerator
  }
  y = y * y % mod; // Multiply by itself to get (n/2)! * (n/2)!
  ll ans = x * qmi(y, mod - 2); // Modular inverse to compute combination C(n, n/2)
  for (int i = 1; i <= n; i++) {
    ans = ans * c[i] % mod; // Multiply by number of ways to color each triangle
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/