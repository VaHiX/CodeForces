// Problem: CF 1433 E - Two Round Dances
// https://codeforces.com/contest/1433/problem/E

#include <cstdio>
typedef long long ll;

/**
 * Calculates the factorial of a number.
 * 
 * Algorithm: Simple iterative multiplication from 1 to x.
 * Time Complexity: O(x)
 * Space Complexity: O(1)
 */
ll fact(ll x) {
  ll res(1);
  for (long p = 1; p <= x; p++) {  // Loop to calculate factorial
    res *= p;
  }
  return res;
}

int main() {
  ll n;
  scanf("%lld", &n);
  
  // Formula explanation:
  // 1. Choose n/2 people out of n for first round dance: C(n, n/2)
  // 2. Arrange them in circle: (n/2 - 1)!
  // 3. Arrange remaining n/2 people in circle: (n/2 - 1)!
  // 4. Since the two round dances are indistinguishable, divide by 2
  // Final formula: (n! / (n/2)! / (n/2)!) * (n/2 - 1)! * (n/2 - 1)! / 2 = n! / ((n/2)! * (n/2)! * 2)
  ll ans = fact(n) / (n / 2) / (n / 2) / 2;
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/