// Problem: CF 1992 C - Gorilla and Permutation
// https://codeforces.com/contest/1992/problem/C

/*
 * Problem: Gorilla and Permutation
 * 
 * Purpose: Construct a permutation of length n such that the difference 
 *          sum of f(i) and g(i) over all prefixes is maximized.
 * 
 * Approach:
 * - The key insight is to place the largest k values first (from k down to m+1), 
 *   followed by the smallest m values (from 1 to m).
 * - This arrangement ensures that:
 *   - f(i) contributes as much as possible (since larger numbers >= k are placed early)
 *   - g(i) remains small (since small numbers <= m are placed at the end)
 * 
 * Time Complexity: O(n) for each test case
 * Space Complexity: O(1) extra space (not counting output)
 * 
 * Algorithms/Techniques:
 * - Greedy strategy based on number placement
 * - Custom permutation construction
 */

#include <stddef.h>
#include <iostream>

using namespace std;
using ll = long long;
#define fi first
#define se second

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  // Place numbers from n down to m+1 (these are >= k and contribute to f(i))
  for (int i = n; i >= m + 1; i--)
    cout << i << " ";
  // Place numbers from 1 to m (these are <= m and contribute to g(i))
  for (int i = 1; i <= m; i++)
    cout << i << " ";
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/