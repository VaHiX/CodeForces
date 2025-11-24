// Problem: CF 1681 D - Required Length
// https://codeforces.com/contest/1681/problem/D

/*
 * Problem: Required Length
 * Algorithm: Depth-First Search (DFS) with pruning
 * 
 * Approach:
 * - We want to make the length of decimal representation of x equal to n.
 * - At each step, we can multiply x by any digit that appears in x.
 * - We use DFS to explore all possible paths, and pruning to avoid unnecessary computations.
 * - Pruning is done using a logarithmic estimation to determine if further exploration can yield a better solution.
 * 
 * Time Complexity: O(9^n), in worst case we might try all digit combinations, but with pruning it's much less.
 * Space Complexity: O(n), due to recursion depth (stack space for DFS).
 */

#include <cmath>
#include <iostream>

using namespace std;
typedef long long ll;
int n, ans;  // n: target length, ans: minimum operations
ll x, g;     // x: current number, g: lower bound for n-digit number (10^(n-1))

void dfs(ll x, int k) {
  // If x is already >= 10^(n-1), we've reached the target length
  if (x >= g) {
    ans = k;  // Update minimum operations
    return;
  }

  // Pruning: if even the best case (multiplying by 9 each time) won't improve ans, stop
  if (k + 1 + log(1.0 * g / x) / log(9) >= ans)
    return;

  ll t = x;
  int S = 0;
  // Build a bitmask of digits present in x
  while (t)
    S |= 1 << (t % 10), t /= 10;

  // Try multiplying x by each digit from 9 down to 2 (since 1 doesn't change x)
  for (int i = 9; i > 1; --i)
    if (S >> i & 1)  // If digit i is present in x
      dfs(x * i, k + 1);
}

int main() {
  cin >> n >> x, ans = 999;  // Read input and initialize answer to large value
  g = 1;
  // Compute g = 10^(n-1), the smallest n-digit number
  for (int i = 1; i < n; ++i)
    g *= 10;
  dfs(x, 0);  // Start DFS from x with 0 operations
  if (ans == 999)
    cout << -1 << '\n';  // No valid path found
  else
    cout << ans << '\n'; // Print minimum operations
}


// https://github.com/VaHiX/CodeForces/