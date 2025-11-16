// Problem: CF 1808 E2 - Minibuses on Venus (medium version)
// https://codeforces.com/contest/1808/problem/E2

/*
Purpose: This code computes the number of "lucky" tickets on Venus, where a ticket is lucky if one of its digits equals the sum of all other digits modulo k.
The number of digits is n, the base system is k, and the result is returned modulo m.

Algorithms/Techniques:
- Modular exponentiation for fast computation
- Mathematical analysis of digit sums and modular arithmetic
- Case-by-case handling for odd/even k and n
- Use of Fermat's little theorem for modular inverse (since m is prime)

Time Complexity: O(k log n + k) - where log n comes from modular exponentiation, and k is for loops.
Space Complexity: O(1) - only using a constant amount of extra space.

*/

#include <stdio.h>
#include <iosfwd>

#define pb push_back
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<LL, LL>
#define MEM(x) memset(x, 0, sizeof(x))
#define x first
#define y second
#define mp make_pair
#define LL long long
#define sqr(x) ((x) * (x))
using namespace std;
int mod;
LL f_pow(LL a, LL b) {
  LL res = 1, temp = a;
  while (b) {
    if (b & 1)
      res = res * temp % mod;
    temp = temp * temp % mod;
    b >>= 1;
  }
  return res;
}
int main() {
  LL n, k;
  scanf("%lld %lld %d", &n, &k, &mod);
  if (k == 1 || n == 1) {
    printf("1\n");
  } else if (n == 1 || n == 2) {
    printf("%lld\n", k);
  } else if (k % 2 == 1) {
    LL x = f_pow(k - 1, n) - f_pow(k, n); // Calculate difference using modular exponentiation
    if (n % 2 == 0)
      x--;
    else
      x++;
    x = mod - x % mod; // Negative mod adjustment
    x = (x % mod + mod) % mod;
    x = x * f_pow(k, mod - 2) % mod * k % mod; // Multiply by modular inverse and k
    for (int i = 0; i < k; i++) {
      if (i * (n % k) % k == i * 2 % k) { // Special condition check
        if (n % 2 == 1)
          x++; // Adjust accordingly
        else
          x--;
      }
    }
    x = (x % mod + mod) % mod;
    printf("%lld\n", x);
  } else {
    LL x = f_pow(k - 2, n) - f_pow(k, n); // Similar logic with different base
    if (n % 2 == 0)
      x -= f_pow(2, n);
    else
      x += f_pow(2, n);
    x = mod - x % mod;
    x = (x % mod + mod) % mod;
    x = x * f_pow(k, mod - 2) % mod * (k / 2) % mod; // Apply modular inverse and division
    LL tot = 0;
    for (int i = 0; i < k; i++) {
      if (i * (n % k) % k == i * 2 % k ||
          (i * (n % k) + k / 2) % k == i * 2 % k) {
        if (n % 2 == 1)
          tot += f_pow(2, n - 1);
        else
          tot -= f_pow(2, n - 1);
      }
    }
    tot = tot % mod * f_pow(2, mod - 2) % mod; // Modular inverse again
    x += tot;
    x = (x % mod + mod) % mod;
    printf("%lld\n", x);
  }
}


// https://github.com/VaHiX/CodeForces/