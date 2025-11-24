// Problem: CF 1671 C - Dolce Vita
// https://codeforces.com/contest/1671/problem/C

/*
C. Dolce Vita
Algorithms/Techniques: Sorting, Greedy, Binary Search (implicit in the loop logic), Prefix Sum
Time Complexity: O(n log n + n * log(max_price)) where n is the number of shops and max_price is the maximum initial price.
Space Complexity: O(n) for storing the array of prices.

The problem simulates buying packs of sugar from different shops over time, with prices increasing each day.
We sort the prices to greedily buy the cheapest packs first to maximize total count.
For each day, we calculate how many packs can be bought within budget by considering increasing prices.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, b;
    scanf("%lld %lld", &n, &b);
    std::vector<ll> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld", &a[p]); // Read the initial prices
    }
    sort(a.begin(), a.end()); // Sort to buy cheapest packs first
    ll cs(0), total(0); // cs: cumulative sum of prices, total: total packs bought
    for (long p = 0; p < n; p++) {
      cs += a[p]; // Add current price to cumulative sum
      if (b < cs) { // If we can't afford all items up to this point
        break; // Stop further purchases on this day
      }
      // Calculate how many full days we can buy 'p+1' packs at least
      total += 1 + (b - cs) / (p + 1); 
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/