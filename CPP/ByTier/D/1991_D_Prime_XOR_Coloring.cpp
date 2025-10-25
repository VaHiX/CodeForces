// Problem: CF 1991 D - Prime XOR Coloring
// https://codeforces.com/contest/1991/problem/D

/*
 * Problem: D. Prime XOR Coloring
 * 
 * Purpose: Color vertices of a graph where an edge exists between u and v if u⊕v is prime,
 *          such that no two adjacent vertices share the same color. Find minimum number of colors.
 * 
 * Approach:
 * - For small values of n (n <= 6), precomputed answers are used.
 * - For larger values of n, it's observed that 4 colors are sufficient due to properties
 *   of XOR and prime numbers, and a cyclic coloring pattern (1,2,3,4,1,2,3,4,...) is used.
 * 
 * Time Complexity: O(n) per test case, since we only iterate through the first 6 values once
 *                  and for larger n we do a linear pass with constant time operations.
 * Space Complexity: O(1) - only fixed size arrays are used (mp, mm, vis), independent of input size.
 */

#include <algorithm>
#include <iostream>

#define X first
#define Y second
using namespace std;
typedef long long ll;

// Precomputed lookup table for small cases
ll mp[310000];
ll mm[310000];

// Precomputed color pattern for small n (1 to 6)
ll vis[10] = {0, 1, 2, 2, 3, 3, 4, 0, 0};

// Standard GCD function (not used in current implementation but defined)
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void solve() {
  ll n, cnt, ans;
  cin >> n;
  
  // If n is small, use precomputed answers
  if (n <= 6) {
    ans = 0;
    for (int i = 1; i <= n; i++) {
      ans = max(ans, vis[i]);  // Find maximum color needed for small inputs
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
      cout << vis[i] << " ";  // Output precomputed colors
    }
    cout << endl;
  } else {
    // For larger n, use a cyclic 4-coloring scheme
    cout << "4" << endl;
    for (int i = 1; i <= n; i++) {
      cout << (i - 1) % 4 + 1 << " ";  // Assign colors in cycle 1,2,3,4,1,2,3,4...
    }
    cout << endl;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  ll T;
  T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/