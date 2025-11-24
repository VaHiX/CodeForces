// Problem: CF 1609 G - A Stroll Around the Matrix
// https://codeforces.com/contest/1609/problem/G

/*
 * Problem: A Stroll Around the Matrix
 * 
 * Algorithm: 
 * - Use a Fenwick Tree (Binary Indexed Tree) to maintain differences in array b
 * - For each operation:
 *   - Add arithmetic progression to suffix of array a.
 *   - Add arithmetic progression to suffix of array b using BIT.
 * - For path calculation:
 *   - Use prefix sums and the BIT to efficiently compute path sum.
 *   - Maintain running sum of b elements.
 * 
 * Time Complexity: 
 *   - Each update operation (addition to array a): O(1) 
 *   - Each update operation (addition to array b): O(log m)
 *   - Each query for path minimum: O(n * log m)
 *   - Total: O(q * (n * log m + log m)) = O(q * n * log m) 
 * 
 * Space Complexity: 
 *   - O(n + m) for arrays a, b, c, and BIT structures.
 * 
 * Techniques:
 * - Fenwick Tree for range updates and prefix sums
 * - Convex property of arrays used in path summation
 * - Efficient calculation of minimum path sum from (1,1) to (n,m)
 */

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int N = 109, M = 100009;
int n, m, q;
ll a[N], b[M], c[M];

// Fenwick Tree implementation for maintaining differences in array b
struct FW {
  ll a[M], b[M];
  
  // Add value y to position x in the BIT
  void add(int x, ll y) {
    for (ll z = x * y; x <= m; x += x & -x)
      a[x] += y, b[x] += z;
  }
  
  // Calculate prefix sum up to x
  ll sum(int x) {
    ll u = 0, v = 0;
    for (int i = x; i; i -= i & -i)
      u += a[i], v += b[i];
    return (x + 1) * u - v;
  }
  
  // Find the index where value x would be inserted in BIT
  int erf(ll x) {
    int r = 0, i = 1 << 18;
    for (; i; i >>= 1)
      if (r + i < m && a[r + i] < x)
        x -= a[r += i];
    return r;
  }
} T;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int i, j, k, l, o, y, las;
  ll ans, sum = 0;
  cin >> n >> m >> q;
  for (i = 1; i <= n; ++i)
    cin >> a[i];
  for (i = 1; i <= m; ++i)
    cin >> b[i], sum += b[i]; // Compute initial sum of array b
  
  // Compute differences between adjacent elements of b
  for (i = 1; i < m; ++i)
    c[i] = b[i + 1] - b[i];
  
  // Initialize the BIT with the differences
  for (i = 1; i < m; ++i)
    T.add(i, c[i] - c[i - 1]);
  
  while (q--) {
    cin >> i >> j >> k;
    if (i == 1) {
      // Update suffix of array a with arithmetic progression
      for (l = n - j + 1, o = 0; l <= n; ++l)
        o += k, a[l] += o;
    } else {
      // Update suffix of array b with arithmetic progression
      if (m == j)
        T.add(1, k), b[1] += k;
      else
        T.add(m - j, k);
      sum += (j + 1ll) * j / 2 * k; // Update the total sum
    }
    
    ans = 0;
    las = 1;
    
    // Calculate minimal path sum using the modified arrays
    for (i = 1; i < n; ++i) {
      y = T.erf(a[i + 1] - a[i]) + 1; // Find position in BIT
      y = min(y, m); // Ensure within bounds
      ans += a[i] * (y - las + 1); // Add contribution from current row
      ans += T.sum(y - 1) + b[1]; // Add sum from BIT and b[1]
      las = y; // Update last position
    }
    
    ans += a[n] * (m - las + 1); // Add final contribution from last row
    cout << ans + sum << '\n'; // Output result with accumulated sum
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/