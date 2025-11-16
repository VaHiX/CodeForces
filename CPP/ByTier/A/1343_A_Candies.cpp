// Problem: CF 1343 A - Candies
// https://codeforces.com/contest/1343/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll m(1); // m will represent (2^p - 1) for increasing values of p
    for (ll p = 1; p < 50; p++) {
      m = 2 * m + 1; // m becomes 2^(p+1) - 1 = (2^p - 1)*2 + 1
      if (n % m) {   // If n is not divisible by m, continue to next p
        continue;
      }
      printf("%lld\n", n / m); // n / m gives the value of x
      break;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/