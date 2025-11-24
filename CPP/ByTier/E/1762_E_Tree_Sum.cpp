// Problem: CF 1762 E - Tree Sum
// https://codeforces.com/contest/1762/problem/E

// Flowerbox
/*
Code Purpose:
This program computes the sum of distances d(1,n) over all "good" edge-weighted trees with n vertices.
A good tree satisfies:
1. Each edge has weight 1 or -1.
2. For each vertex i, the product of edge weights on edges incident to i is -1.

Algorithm:
- Uses combinatorics and generating functions to compute sum of distances efficiently.
- Applies inclusion-exclusion to count contributions from different configurations.
- Precomputes factorials and modular inverses for fast computation.

Time Complexity: O(n)
Space Complexity: O(n)

Techniques:
- Modular exponentiation
- Precomputation of factorials and inverses
- Combinatorial sum calculation with inclusion-exclusion
*/
// End Flowerbox

#include <stdint.h>

#import <iostream>
const int N = 6e5, p = 998244353;
using ll = int64_t;

// Fast modular exponentiation
ll m(ll x, int b) {
  ll r = 1;
  for (; b; b >>= 1, x = x * x % p)
    if (b & 1)
      r = r * x % p;
  return r;
}

// Precomputed arrays for factorials, inverse factorials, and inverse elements
ll fc[N], ifc[N], iv[N], r, i, n;

// Combination function C(x, y) = x! / (y! * (x - y)!)
ll c(ll x, ll y) { return fc[x] * ifc[y] % p * ifc[x - y] % p; }

int main() {
  // Precompute factorials and inverse factorials
  for (fc[0] = fc[1] = ifc[0] = ifc[1] = iv[1] = 1, i = 2; i < N; i++)
    fc[i] = fc[i - 1] * i % p, // factorial
    iv[i] = (p - p / i) * iv[p % i] % p, // modular inverse
    ifc[i] = ifc[i - 1] * iv[i] % p; // inverse factorial

  // Read input
  for (std::cin >> n, i = 1; i < n; i++)
    // Calculate contribution of each configuration
    // r accumulates sum of weighted contributions
    (r += m(i, i - 1) * m(n - i, n - i - 1) % p * c(n - 2, i - 1) * (1 - (i & 1) * 2)) %= p;

  // Output result, ensuring non-negative modulo
  std::cout << (r + p) % p;
}


// https://github.com/VaHiX/CodeForces/