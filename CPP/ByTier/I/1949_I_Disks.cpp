// Problem: CF 1949 I - Disks
// https://codeforces.com/contest/1949/problem/I

/*
 * Problem: Changing Radii of Disks
 *
 * Purpose:
 *   Determine whether it's possible to change the radii of given disks such that:
 *   - Disks that were tangent remain tangent
 *   - No two disks overlap in a region of positive area
 *   - The sum of all radii strictly decreases
 *   - Centers cannot be changed, only radii can be adjusted.
 *
 * Algorithm:
 *   - Build a graph where nodes represent disks and edges connect disks that were initially tangent.
 *   - For each connected component in the graph:
 *     * Attempt to assign colors (0 or 1) to disks such that adjacent disks have different colors.
 *     * This checks if there's an assignment of radii that allows valid distances while decreasing the total sum.
 *   - If such a coloring leads to a valid decrease in total radius, output "YES".
 *   - Otherwise, output "NO".
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define eb emplace_back
using namespace std;
typedef long long ll;
const ll _ = 1005;
inline ll sq(ll x) { return x * x; }
ll n, t, f[_], i, j;
vector<ll> E[_]; // adjacency list for graph of tangent disks
struct o {
  ll x, y, r;
} a[_];
// Check if two disks are tangent (distance between centers equals sum of radii)
inline bool p1(o x, o y) {
  return sq(x.x - y.x) + sq(x.y - y.y) == sq(x.r + y.r);
}
// DFS traversal to color the graph and track the total adjustment
inline void p2(ll x) {
  t += (f[x] == 2 ? 1 : -1); // adjust counter based on current node's color
  for (auto y : E[x]) {       // iterate adjacent nodes
    if (!f[y])
      f[y] = f[x] ^ 1, p2(y); 
    else if (f[x] ^ f[y] ^ 1)
      t = 1e9; // conflict detected -> invalid configuration
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (i = 1; i <= n; i++)
    cin >> a[i].x >> a[i].y >> a[i].r;
  // Build adjacency list of tangent disks
  for (i = 1; i < n; i++)
    for (j = i + 1; j <= n; j++)
      if (p1(a[i], a[j]))
        E[i].eb(j), E[j].eb(i);
  // Process each connected component
  for (i = 1; i <= n; i++)
    if (!f[i]) {
      t = 0;
      f[i] = 2;  // mark as unvisited but used in DFS context
      p2(i);
      if (t != 0 && t <= n)
        return cout << "YES\n", 0;
    }
  cout << "NO\n";
}


// https://github.com/VaHiX/codeForces/