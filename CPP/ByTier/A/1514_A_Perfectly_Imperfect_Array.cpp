// Problem: CF 1514 A - Perfectly Imperfect Array
// https://codeforces.com/contest/1514/problem/A

/*
Problem: A. Perfectly Imperfect Array
Purpose: Determine if there exists a subsequence in the given array whose product is not a perfect square.

Algorithm:
- Precompute all perfect squares up to 107^2 (since max element is 10^4, we only need to check up to sqrt(10^4) = 100)
- For each test case:
  - Read array elements
  - Check if any element in the array is not a perfect square
  - If yes, then we can form a subsequence with non-perfect square product (just that one element)
  - If all elements are perfect squares, then all possible products will also be perfect squares

Time Complexity: O(n) per test case where n is the size of array
Space Complexity: O(1) since we precompute a fixed set of squares up to 107^2

Techniques:
- Precomputation of perfect squares using a set for fast lookup
- Greedy approach: If any element itself is not a perfect square, answer is YES
*/

#include <cstdio>
#include <set>
typedef long long ll;

int main() {
  std::set<ll> s;
  // Precompute all perfect squares from 0 to 107^2 (enough for elements up to 10^4)
  for (ll p = 0; p < 107; p++) {
    s.insert(p * p);
  }
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    bool res(false);
    // For each element in current test case
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // If current element is not a perfect square, we can form a non-perfect square product
      if (!(s.count(x))) {
        res = true;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/