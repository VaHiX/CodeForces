// Problem: CF 983 A - Finite or not?
// https://codeforces.com/contest/983/problem/A

/*
 * Problem: Determine if the fraction p/q in base b has a finite representation.
 * 
 * Algorithm:
 * - Reduce the fraction p/q to its simplest form by dividing by GCD(p, q).
 * - Then, check if the denominator q (after simplification) has only prime factors that are also factors of the base b.
 * - This is done by repeatedly removing common prime factors between q and b until either q becomes 1 (finite) or b becomes 1 (infinite).
 * 
 * Time Complexity: O(log(q) * log(b)) per query due to GCD operations and loop.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void solve() {
  ll p, q, b;
  scanf("%lld%lld%lld", &p, &q, &b);
  ll g = __gcd(p, q);  // Get the greatest common divisor of p and q
  q /= g;  // Simplify q by dividing with GCD
  while (q != 1 && b != 1) {
    ll b_gcd = __gcd(q, b);  // Find common factors of q and b
    if (b_gcd == 1) break;  // No more common factors
    q /= b_gcd;  // Remove the common factor from q
    b = b_gcd;  // Update b to the common factor
  }
  if (q == 1)
    puts("Finite");  // If q becomes 1, the fraction is finite
  else
    puts("Infinite");  // Otherwise it's infinite
}

int main() {
  int n;
  scanf("%d", &n);
  while (n--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/