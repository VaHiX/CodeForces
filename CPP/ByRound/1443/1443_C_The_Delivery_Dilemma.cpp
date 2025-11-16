// Problem: CF 1443 C - The Delivery Dilemma
// https://codeforces.com/contest/1443/problem/C

/*
C. The Delivery Dilemma
Algorithm: Greedy + Sorting + Prefix Sum
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing pairs and prefix sums

Problem:
Petya wants to order n dishes from different restaurants. For each dish,
he can either:
1. Get it delivered by courier in a[i] minutes.
2. Go to the restaurant himself and pick it up in b[i] minutes.

All couriers start delivering at the same time Petya leaves his house.
Petya visits restaurants he doesn't choose delivery in sequence (b[i] times).
Find minimum time for all dishes to be ready.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> t(n); // Store (a[i], b[i]) for each dish
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &t[p].first); // Read delivery time a[i]
    }
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &t[p].second); // Read pickup time b[i]
    }
    sort(t.begin(), t.end()); // Sort by delivery time 'a' in ascending order
    
    // Build suffix sum of pickup times
    for (ll p = n - 2; p >= 0; p--) {
      t[p].second += t[p + 1].second; // t[p].second now holds sum of b[i] from index p to n-1
    }
    
    ll ans(t[0].second); // Initialize answer with total pickup time if no delivery used
    
    for (ll p = 0; p < n; p++) {
      ll pt = (p + 1 < n) ? t[p + 1].second : 0; // Sum of b[i] from p+1 to end
      ll dt = t[p].first; // Delivery time of current dish
      
      // Total time: max of:
      // - pt: time for remaining dishes (delivery), 
      // - dt: time for the current dish if picked up
      ll total = (pt > dt) ? pt : dt;
      
      ans = (ans < total) ? ans : total; // Update minimum time
      
      // If picking this dish is faster than delivering it, we should stop here
      if (dt > pt) {
        break;
      }
    }
    
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/