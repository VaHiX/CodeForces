// Problem: CF 913 C - Party Lemonade
// https://codeforces.com/contest/913/problem/C

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const int B = 33;
  ll n, L;
  scanf("%lld %lld", &n, &L);
  ll x(L);
  std::vector<int> bv(B, 0);
  for (ll p = 0; p < B; p++) {
    bv[p] = x % 2; // Store binary representation of L
    x /= 2;
  }
  std::vector<ll> price(B, 0);
  for (ll p = 0; p < n; p++) {
    ll y;
    scanf("%lld", &y);
    price[p] = y;
    if ((p > 0) && (2 * price[p - 1] < y)) {
      price[p] =
          2 *
          price[p - 1]; // Optimize price by taking advantage of smaller powers
    }
  }
  for (ll p = n; p < B; p++) {
    price[p] = 2 * price[p - 1]; // Extend the price vector to B elements
  }
  ll cost(0);
  for (ll p = 0; p < B; p++) {
    ll a = cost + bv[p] * price[p]; // Cost if we include this bottle
    ll b =
        (1 + bv[p]) *
        price[p]; // Cost if we don't include this bottle (but we may need more)
    cost = (a < b) ? a : b; // Choose the minimum cost
  }
  printf("%lld\n", cost);
  return 0;
}

// ### Algorithm and Complexity Analysis:

// **Algorithm**: This code solves the problem using dynamic programming with
// bitmask representation of the required amount of lemonade (`L`). It
// interprets `L` as a binary number and uses the idea that we can combine
// smaller powers of 2 (bottle sizes) to form larger amounts. The key insight is
// to optimize bottle prices such that a bottle of size `2^i` costs no more than
// twice the price of `2^(i-1)` – this allows for cheaper combinations.

// **Time Complexity**: O(n + B), where `n` is the number of bottle types and `B
// = 33` (since `L` is up to `10^9` and we need at most 31 bits plus one more
// for safety). The operations on the vector are linear in the size of `n` and
// fixed constant `B`.

// **Space Complexity**: O(B), as we use vectors of size `B` to store binary
// representation of `L` and optimized bottle prices.

// https://github.com/VaHiX/CodeForces/