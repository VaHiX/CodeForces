// Problem: CF 1607 B - Odd Grasshopper
// https://codeforces.com/contest/1607/problem/B

/*
B. Odd Grasshopper
Purpose: Calculate the final position of a grasshopper after n jumps,
         where each jump distance equals the jump number (1, 2, 3, ...),
         and direction depends on the parity of current coordinate:
         even -> left, odd -> right.

Algorithms/Techniques: Mathematical pattern recognition, modular arithmetic.
Time Complexity: O(1) per test case.
Space Complexity: O(1).

The grasshopper's movement follows a predictable cycle every 4 jumps,
so we can compute the result in constant time using modulo operations.
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, n;
    scanf("%lld %lld", &x, &n);
    ll res(x), s(x % 2 ? 1 : -1); // s is -1 if x is even, 1 if x is odd
    if (n % 4 == 1) {
      res += s * n; // Add n when remainder is 1, using sign s
    } else if (n % 4 == 2) {
      res -= s;     // Subtract s when remainder is 2
    } else if (n % 4 == 3) {
      res -= s * (n + 1); // Subtract (n+1)*s when remainder is 3
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/