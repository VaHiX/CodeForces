// Problem: CF 1842 H - Tenzing and Random Real Numbers
// https://codeforces.com/contest/1842/problem/H

/*
 * Problem: H. Tenzing and Random Real Numbers
 * 
 * Algorithm: Dynamic Programming with Bitmasking
 * 
 * Purpose:
 *   Given n uniform random variables in [0,1], and m conditions of the form
 *   x_i + x_j <= 1 or x_i + x_j >= 1, we calculate the probability that all
 *   conditions are satisfied. Uses bitmask DP to enumerate valid combinations
 *   of assignments and compute the final probability modulo 998244353.
 * 
 * Time Complexity: O(2^n * n)
 * Space Complexity: O(2^n)
 * 
 * Techniques:
 *   - Bitmask Dynamic Programming
 *   - Modular arithmetic with inverse modulo
 *   - Condition checking using bitmasks
 */

#include <stdio.h>
#include <iostream>

#define lep(i, l, r) for (int i = (l); i <= (r); i++)
#define rep(i, l, r) for (int i = (l); i >= (r); i--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
using std ::cerr;
using std ::cin;
using std ::cout;
using std ::endl;
using i64 = long long;
const int P = 998244353;
inline int mod(int x) { return x + (x >> 31 & P); }
inline void sub(int &x, int y) { x = mod(x - y); }
inline void pls(int &x, int y) { x = mod(x + y - P); }
inline int add(int x, int y) { return mod(x + y - P); }
inline int dec(int x, int y) { return mod(x - y); }
inline int power(int x, int k) {
  int res = 1;
  if (k < 0)
    k += P - 1;
  while (k) {
    if (k & 1)
      res = 1ll * res * x % P;
    x = 1ll * x * x % P;
    k >>= 1;
  }
  return res;
}
int main() {
  std ::ios ::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  static int lim[20][2], f[1 << 20];
  // Read and process conditions, storing in bitmasks
  while (m--) {
    int o, x, y;
    cin >> o >> x >> y;
    --x, --y;
    lim[x][o] |= 1 << y; // Store y in bitmask for condition type o for x
    lim[y][o] |= 1 << x; // Similarly for y
  }
  f[0] = 1; // Base case: empty set has one valid assignment
  // Iterate through each subset of variables and extend valid assignments
  lep(S, 0, (1 << n) - 1) lep(i, 0, n - 1) if (!(S & (1 << i))) {
    // For variable i not yet assigned:
    if ((S & lim[i][0]) == lim[i][0])
      pls(f[S | (1 << i)], f[S]); // If x_i + x_j <= 1 is satisfied, extend
    if ((S & lim[i][1]) == lim[i][1])
      pls(f[S | (1 << i)], f[S]); // If x_i + x_j >= 1 is satisfied, extend
  }
  // Calculate total valid assignments (probability) and modular inverse
  int inv = 1;
  lep(i, 1, n) inv = 1ll * inv * i % P; // Factorial of n (permutations)
  inv = 1ll * inv * power(2, n) % P; // Multiply by 2^n for all real number pairs
  inv = power(inv, P - 2); // Modular inverse using Fermat's little theorem
  cout << 1ll * inv * f[(1 << n) - 1] % P << endl; // Final result
  return 0;
}


// https://github.com/VaHiX/CodeForces/