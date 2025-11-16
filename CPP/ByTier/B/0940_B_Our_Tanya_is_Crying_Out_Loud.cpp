// Problem: CF 940 B - Our Tanya is Crying Out Loud
// https://codeforces.com/contest/940/problem/B

/*
 * Problem: Make x equal to 1 with minimum cost using two operations:
 *          1. Subtract 1 from x (costs A coins)
 *          2. Divide x by k if divisible (costs B coins)
 *
 * Algorithm: Dynamic Programming with Memoization (DFS + Map)
 *            - For each x, decide whether to:
 *              a) Divide by k (if possible) and pay B
 *              b) Subtract 1 multiple times and pay A each time
 *            - Use memoization to avoid recomputation
 *
 * Time Complexity: O(log_k(n)) due to recursive depth and memoization
 * Space Complexity: O(log_k(n)) for the recursion stack and map storage
 */

#include <cstdio>
#include <map>
typedef long long ll;

// Function to compute minimum cost to reduce x to 1
ll getCost(ll x, const ll &k, const ll &a, const ll &b, std::map<ll, ll> &m) {
  if (x == 1) {
    return 0;
  } else if (k <= 1 || k > x) {
    // If k <= 1 or x < k, we can't divide, so subtract all the way
    return (a * (x - 1));
  } else if (m.count(x)) {
    // Return precomputed result if available
    return m[x];
  } else if (x % k == 0) {
    // x is divisible by k, so we can divide
    // Compare cost of dividing vs subtracting to reach next divisible number
    ll cur = getCost(x / k, k, a, b, m) +
             ((b < (x - x / k) * a) ? b : ((x - x / k) * a));
    m[x] = cur;
    return cur;
  } else {
    // x is not divisible by k
    // Find the largest multiple of k <= x, subtract to get there, then divide
    ll mult = k * (x / k);
    ll cur = getCost(mult, k, a, b, m) + (x - mult) * a;
    m[x] = cur;
    return cur;
  }
  return 0;
}

int main() {
  ll n, k, a, b;
  scanf("%lld %lld %lld %lld", &n, &k, &a, &b);
  std::map<ll, ll> m;
  m[1] = 0;  // Base case: cost to make 1 is 0
  ll ans = getCost(n, k, a, b, m);
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/