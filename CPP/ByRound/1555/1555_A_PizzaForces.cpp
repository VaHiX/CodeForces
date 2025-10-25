// Problem: CF 1555 A - PizzaForces
// https://codeforces.com/contest/1555/problem/A

/*
 * Problem: PizzaForces
 * Algorithm: Greedy with mathematical optimization
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The problem asks for the minimum baking time to obtain at least n slices of pizza.
 * We have three types of pizzas:
 * - Small: 6 slices, 15 minutes
 * - Medium: 8 slices, 20 minutes  
 * - Large: 10 slices, 25 minutes
 *
 * To minimize time, we want to maximize the number of slices per minute.
 * However, since we must get at least n slices, we can use a greedy approach:
 * - If n <= 6, we only need one small pizza (6 slices).
 * - Otherwise, we can compute how many slices are needed and choose optimal combination.
 *
 * The trick here is to observe that the minimum time can always be achieved by:
 * 1. Using the maximum possible number of large pizzas (since they give best ratio),
 * 2. Then filling remaining with medium or small as needed,
 * 3. But due to the small constraints, we can simplify it mathematically.
 *
 * The key insight is that for n >= 6, we just compute:
 * - Minimum slices needed: n
 * - If n <= 6, make one small pizza (time = 15)
 * - Else calculate optimal grouping using ceiling of n/2 * 5, which works due to
 *   the special properties of slices and times involved.
 */

#include <cstdio>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    // If n <= 6, we can only make a small pizza (6 slices)
    n = (n > 6) ? n : 6;
    // Compute result using formula: (n + 1) / 2 * 5
    // This effectively calculates minimum time to get at least n slices
    ll res = (n + 1) / 2 * 5;
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/