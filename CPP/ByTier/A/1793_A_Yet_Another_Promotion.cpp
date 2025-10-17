// Problem: CF 1793 A - Yet Another Promotion
// https://codeforces.com/contest/1793/problem/A

/*
 * Problem: A. Yet Another Promotion
 * Purpose: Find the minimum cost to buy at least n kilos of potatoes,
 *          considering price differences on two days and a promotion
 *          on the first day where buying m kilos grants 1 extra kilo.
 *
 * Algorithms/Techniques:
 *   - Greedy approach with mathematical optimization
 *   - Minimize cost by choosing optimal combination of:
 *     * Buying in batches of (m+1) kilos using promotion (cost = m*a)
 *     * Buying remaining kilos individually at day 2 price (cost = b)
 *     * Or buying remaining kilos individually at day 1 price (cost = a)
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll n, m;
    scanf("%lld %lld", &n, &m);

    // Calculate cost for buying full batches of (m+1) kilos using promotion
    ll cfa = m * a * (n / (m + 1));  // Cost when buying with promotion on day 1
    ll cfb = (m + 1) * b * (n / (m + 1));  // Cost when buying same amount on day 2
    
    ll cf = (cfa < cfb) ? cfa : cfb;  // Choose cheaper between two strategies

    // Remaining potatoes after full batches
    ll cs = (a < b ? a : b) * (n % (m + 1));  // Cost for remaining kilos with optimal day
    
    ll cost = cf + cs;
    printf("%lld\n", cost);
  }
}


// https://github.com/VaHiX/codeForces/