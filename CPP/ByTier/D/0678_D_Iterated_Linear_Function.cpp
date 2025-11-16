// Problem: CF 678 D - Iterated Linear Function
// https://codeforces.com/contest/678/problem/D

/*
 * Calculates the nth iteration of a linear function f(x) = Ax + B
 * using fast exponentiation technique.
 * 
 * The recurrence relation is:
 * g^0(x) = x
 * g^n(x) = f(g^(n-1)(x)) = A * g^(n-1)(x) + B
 * 
 * This is solved using matrix exponentiation concept:
 * [ g(n) ]   [ A  B ] [ g(n-1) ]
 * [   1    ] = [ 0  1 ] [   1    ]
 * 
 * But optimized with the idea that:
 * - If n is odd, apply the function once
 * - Otherwise, square the transformation matrix and halve n
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  ll a, b, n, x;
  scanf("%lld %lld %lld %lld", &a, &b, &n, &x);
  while (n > 0) {
    if (n % 2) {
      // Apply function f(x) = Ax + B
      x = (a * x + b) % MOD;
    }
    // Update coefficients for next iteration using matrix exponentiation trick
    b *= (a + 1);
    b %= MOD;
    a *= a;
    a %= MOD;
    n /= 2;
  }
  printf("%lld\n", x);
  return 0;
}


// https://github.com/VaHiX/CodeForces/