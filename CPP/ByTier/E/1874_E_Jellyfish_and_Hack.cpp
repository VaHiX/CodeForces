// Problem: CF 1874 E - Jellyfish and Hack
// https://codeforces.com/contest/1874/problem/E

/*
 * Problem: Jellyfish and Hack
 * Purpose: Count the number of permutations of [1, 2, ..., n] such that the 
 *          quicksort-like function `fun(P)` is greater than or equal to `lim`.
 *          The function computes the number of comparisons made in a specific 
 *          quicksort variant where the first element is always chosen as pivot.
 *
 * Algorithms/Techniques:
 * - Dynamic Programming with generating functions and inclusion-exclusion
 * - Fast exponentiation for modular arithmetic
 * - Combinatorial mathematics and modular inverse
 * - Preprocessing factorials and their modular inverses
 *
 * Time Complexity: O(n^2 * log(n)) due to nested loops and modular exponentiation.
 * Space Complexity: O(n) for storing arrays and helper structures.
 *
 * Input:
 *   n: Size of permutation (1 <= n <= 200)
 *   lim: Threshold for the function output (1 <= lim <= 10^9)
 *
 * Output:
 *   Count of valid permutations modulo 10^9 + 7.
 */

#include <iostream>

using namespace std;
#define int long long
#define f(i, j, k) for (int i = j; i <= k; ++i)
#define g(i, j, k) for (int i = j; i >= k; --i)
int n, m, s, l;
const int N = 20202, V = 20123, mo = 1e9 + 7;

// Fast modular exponentiation
inline int ksm(int x, int p = mo - 2, int y = 1) {
  for (; p; p /= 2, x = x * x % mo)
    if (p & 1)
      y = x * y % mo;
  return y;
}

int jc[N], ny[N], a[N], f[N], x, y, z;

// Main function
signed main() {
  cin >> n >> m;
  jc[0] = 1;
  f(i, 1, V) jc[i] = jc[i - 1] * i % mo; // Precompute factorials
  ny[V] = ksm(jc[V]); // Precompute modular inverse of factorial
  g(i, V, 1) ny[i - 1] = ny[i] * i % mo; // Inverse of factorials backwards
  a[0] = f[1] = 1;
  f(i, 1, V) g(k, i + 1, 1) f[k] = (f[k - 1] - i * f[k]) % mo; // Precompute Stirling numbers
  f(i, 1, V) {
    f(j, 1, n) {
      y = 0;
      f(k, 1, j) {
        y += a[k - 1] * a[j - k]; // Contribution from partitioning
        if ((k & 7) == 0) // Optimization to reduce overflow
          y %= mo;
      }
      a[j] = y % mo * jc[j - 1] % mo * ny[j] % mo * ksm(i, j) % mo; // Compute coefficients
    }
    x = ny[i] * jc[i - 1] % mo; // Modular inverse
    y = 0;
    z = 1;
    g(k, V, m + 1) {
      y += z; // Accumulate
      z = i * z + f[k]; // Update for inclusion-exclusion
      if (k & 1) // Handle negative signs or modular adjustments
        z %= mo;
    }
    s = (s + (y % mo + mo) * a[n] % mo * jc[n] % mo * ny[i - 1] % mo *
                 ny[V - i] % mo * ksm(mo - 1, V - i)) %
        mo; // Final modular update and accumulation
  }
  cout << s;
  return 0;
}


// https://github.com/VaHiX/CodeForces/