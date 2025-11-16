// Problem: CF 1810 H - Last Number
// https://codeforces.com/contest/1810/problem/H

/*
Code Purpose:
This code solves the problem of finding the last remaining number in a multiset after performing a series of operations where the largest and smallest elements are removed and their difference is added back. The solution uses a mathematical approach based on the properties of the operations and a recursive function with precomputed constants to calculate the result efficiently.

Algorithms/Techniques:
- Mathematical simulation using recursive G function with modular arithmetic
- Binary search or mathematical mapping via precomputed constants
- Optimized computation using integer arithmetic and bit manipulation

Time Complexity: O(1) per test case (due to precomputed constants and direct calculation)
Space Complexity: O(1) (only a few variables used)
*/

#include <iostream>

#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;

// Recursive helper function to compute a specific summation using continued fractions or modular arithmetic
inline LL G(LL n, LL R, LL P, LL Q) {
  LL z = 0;
  if (Q >= R)
    z += Q / R * n, Q %= R;
  if (P >= R)
    z += P / R * n * (n - 1) / 2, P %= R;
  const LL X = (P * n + Q) / R;
  if (!X)
    return z;
  const LL Y = X * R - Q, Z = -Y % P;
  return z + (n - (Y + P - 1) / P) * X + G(X, P, R, Z < 0 ? Z + P : Z);
}

// Main logic to compute the final answer for a given n
inline void MAIN() {
  int n;
  cin >> n;
  // Precomputed constant for calculating m
  int m = (n + 1) * 1134903170ll / 2971215073;
  LL ans = 0;
  // Apply G function with different parameters to get components of answer
  ans += G((m + 1) / 2, 1134903170, 1402817466, 701408733) -
         G(m / 2 + 1, 1134903170, 1402817466, 0);
  ans -= G(n / 2, 1134903170, 1402817466, 701408733) -
         G((n + 1) / 2, 1134903170, 1402817466, 0);
  // Adjust sign if n is odd
  if (n & 1)
    ans *= -1;
  // Adjust final answer based on parity of (n - m)
  if ((n - m) & 1)
    ans += n - n * 701408733ll / 1134903170;
  else
    ans += n * 701408733ll / 1134903170;
  cout << ans << '\n';
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t = 1;
  cin >> t;
  while (t--)
    MAIN();
  return 0;
}


// https://github.com/VaHiX/CodeForces/