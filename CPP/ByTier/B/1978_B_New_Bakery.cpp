// Problem: CF 1978 B - New Bakery
// https://codeforces.com/contest/1978/problem/B

/*
B. New Bakery
Algorithm: Greedy + Mathematical Optimization
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves maximizing profit by choosing an optimal value of k,
where the first k buns are sold at decreasing prices (b, b-1, ..., b-k+1),
and the remaining n-k buns are sold at price a each.

To maximize profit:
- When b > a, it's better to sell some buns at higher prices.
- We compute the sum of arithmetic progression for first k buns and add
  the cost of remaining (n-k) buns.
- The optimal k is determined by balancing the gain from premium pricing
  against the loss from selling fewer high-priced buns.

The key insight is to calculate profit as:
profit = (sum of first k terms of arithmetic sequence: b, b-1, ..., b-k+1)
         + (n-k) * a

This simplifies to:
profit = k*b - k*(k-1)/2 + (n-k)*a
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);
    
    ll k = b - a;                        // Decide how many buns to sell at premium price
    k = (k > 0 ? k : 0);                 // Ensure k is non-negative
    k = (k < n ? k : n);                 // Cap k at n
    
    // Calculate total profit:
    // - (b * k) gives initial sum of arithmetic sequence, minus correction term
    // - k*(k-1)/2 is the sum of 0+1+...+(k-1), needed to adjust the arithmetic sequence
    // - (n-k)*a accounts for remaining buns at standard price
    ll total = b * k - k * (k - 1) / 2 + (n - k) * a;
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/