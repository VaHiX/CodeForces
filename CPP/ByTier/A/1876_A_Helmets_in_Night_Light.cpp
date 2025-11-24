// Problem: CF 1876 A - Helmets in Night Light
// https://codeforces.com/contest/1876/problem/A

/*
 * Problem: A. Helmets in Night Light
 * Algorithms/Techniques: Greedy algorithm
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the vector of pairs
 *
 * The problem is about minimizing the cost to notify all residents.
 * Initially, Pak Chanek can directly inform some residents at cost 'p' each.
 * Then those notified residents can spread the message using helmets,
 * where each resident i can share with at most a[i] others at cost b[i] per share.
 *
 * Strategy:
 * 1. Sort residents by their sharing cost (b[i]) in ascending order to use greedy approach.
 * 2. First, directly inform as many residents as possible such that their cost is less than p,
 *    but we must ensure all are covered. We use a greedy method to select the cheapest
 *    sharing costs first and calculate how many we can send.
 * 3. Add the remaining (n - rem) people who are not yet informed and each will cost 'p' directly.
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
    ll n, r; // n: number of residents, r: cost to notify one directly
    scanf("%lld %lld", &n, &r);
    std::vector<std::pair<ll, ll>> v(n); // pair: {cost_to_share, max_shares_allowed}
    
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p].second); // a[i]: max shares allowed
    }
    
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p].first); // b[i]: cost per share
    }
    
    sort(v.begin(), v.end()); // Sort by cost to share ascending
    
    ll rem(n - 1), total(r); // Initially only we inform one person directly, so (n-1) remain to be spread
    for (ll p = 0; p < n; p++) {
      if (v[p].first >= r) { // Stop if the cost is higher than direct notification cost
        break;
      }
      ll cnt = (rem < v[p].second) ? rem : v[p].second; // How many we can notify via this person
      total += cnt * v[p].first; // Add to total cost
      rem -= cnt; // Reduce the number of people left to notify
    }
    
    total += r * rem; // For remaining people, directly inform them at cost 'r'
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/