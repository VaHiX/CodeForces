// Problem: CF 1619 B - Squares and Cubes
// https://codeforces.com/contest/1619/problem/B

/*
B. Squares and Cubes
Algorithm: Generate all perfect squares and cubes up to 1e9, store in a set to avoid duplicates.
For each query, count how many generated numbers are <= n.

Time Complexity: O(sqrt(1e9) + cbrt(1e9) + t) = O(10^5 + 10^3 + t)
Space Complexity: O(sqrt(1e9) + cbrt(1e9)) = O(10^5)

Techniques:
- Set for deduplication
- Precomputation of all valid numbers
- Iteration through set to count elements <= n
*/

#include <cstdio>
#include <set>
typedef long long ll;
int main() {
  std::set<ll> s;  // Set to store unique perfect squares and cubes
  for (ll p = 1; p * p <= 1e9; p++) {  // Generate all perfect squares up to 1e9
    s.insert(p * p);
  }
  for (ll p = 1; p * p * p <= 1e9; p++) {  // Generate all perfect cubes up to 1e9
    s.insert(p * p * p);
  }
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(0);
    for (std::set<ll>::iterator it = s.begin(); ((*it) <= n) && it != s.end();
         it++) {  // Count elements in set <= n
      ++cnt;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/