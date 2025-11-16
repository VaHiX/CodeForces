// Problem: CF 1768 E - Partial Sorting
// https://codeforces.com/contest/1768/problem/E

/*
Code Purpose:
This code computes the sum of the minimum number of operations f(p) over all (3n)! permutations p of size 3n,
where each operation sorts either the first 2n or the last 2n elements of the permutation.
The result is returned modulo a prime M.

Algorithms/Techniques:
- Preprocessing factorials and their modular inverses
- Mathematical combinatorics and inclusion-exclusion principles
- Modular exponentiation for computing inverses
- Dynamic programming and summation techniques with modular arithmetic

Time Complexity: O(3n)
Space Complexity: O(3n)

*/

#include <cstdio>
#include <iosfwd>

#define ll long long
using namespace std;

ll F[3000001], G[3000001]; // F[i] stores i!, G[i] stores modular inverse of i!

// Fast modular exponentiation
ll pow(ll x, ll y, ll z) {
  if (y == 0)
    return 1;
  ll t = pow(x, y / 2, z);
  t = t * t % z;
  if (y % 2)
    return t * x % z;
  return t;
}

int main() {
  ll n, M;
  scanf("%lld%lld", &n, &M);
  
  // Precompute factorials
  F[0] = 1;
  for (ll i = 1; i <= 3 * n; ++i)
    F[i] = F[i - 1] * i % M;
  
  // Precompute modular inverses of factorials
  G[3 * n] = pow(F[3 * n], M - 2, M); // Modular inverse of (3n)! using Fermat's little theorem
  for (ll i = 3 * n - 1; i >= 0; --i)
    G[i] = G[i + 1] * (i + 1) % M;
  
  // a: number of permutations requiring 0 operations
  ll a = 1;
  
  // b: number of permutations requiring 1 operation
  ll b = (2 * F[2 * n] - F[n]) % M;
  
  // s: summation term used in calculation of c
  ll s = 0;
  for (ll i = 0; i <= n; ++i) {
    s += F[2 * n - i] * G[i] % M * G[i] % M * pow(G[n - i], 3, M) % M;
    s %= M;
  }
  
  // c: number of permutations requiring 2 operations
  ll c = (2 * F[2 * n] * F[2 * n] % M * G[n] % M - s * pow(F[n], 4, M) % M) % M;
  
  // d: total permutations (3n)!
  ll d = F[3 * n];
  
  // r: number of permutations requiring 3 operations
  ll r = (3 * d - a - b - c) % M;
  if (r < 0)
    r += M;
  
  printf("%lld", r);
}


// https://github.com/VaHiX/CodeForces/