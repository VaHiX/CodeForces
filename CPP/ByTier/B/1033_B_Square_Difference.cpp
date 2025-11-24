// Problem: CF 1033 B - Square Difference
// https://codeforces.com/contest/1033/problem/B

/*
B. Square Difference
Algorithm: For each test case, compute the area of the remaining cloth as a^2 - b^2,
           which equals (a+b)(a-b). Check if this value is prime.

Time Complexity: O(sqrt(a+b)) per test case, since we check divisibility up to sqrt(a+b)
Space Complexity: O(1), only using constant extra space

The key insight is that a^2 - b^2 = (a+b)(a-b). Since a > b, both (a+b) and (a-b) are positive.
If the result is prime, it must be greater than 1 and have no divisors other than 1 and itself.
However, if (a+b) > 1 and (a-b) > 1, then the product cannot be prime.
So we only need to check if a+b == 1 or a-b == 1 after ensuring a > b+1.
But that isn't necessary for this problem's logic.

The code directly checks if (a^2 - b^2) is prime by trial division up to sqrt(a^2 - b^2).
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    if (a > b + 1) { // Check if area can be prime
      puts("NO");
      continue;
    }
    ll s = a + b; // Area is (a^2 - b^2) = (a+b)(a-b). Since a > b, (a-b) >= 1.
                  // If a == b+1, then a-b = 1, so area = (a+b)*1 = a+b.
    bool res(true); // Initially assume result is prime
    for (ll p = 2; p * p <= s; p++) { // Trial division to check if s is prime
      if (s % p == 0) {
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/