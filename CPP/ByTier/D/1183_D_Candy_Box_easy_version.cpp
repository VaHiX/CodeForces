// Problem: CF 1183 D - Candy Box (easy version)
// https://codeforces.com/contest/1183/problem/D

/*
D. Candy Box (easy version)
Algorithm: Greedy approach with sorting
Time Complexity: O(n log n) per query due to sorting
Space Complexity: O(n) for storing counts and vector

The problem asks to find the maximum number of candies that can be selected such that
the count of each candy type in the selection is unique. This means if we have 3 candies
of type A, we can only select at most 3 candies from type A. Then, we sort the counts in
descending order and greedily take the maximum possible values while ensuring all counts
remain distinct.
*/

#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll n;
    scanf("%lld", &n);
    std::map<ll, ll> cnts; // Count occurrences of each candy type
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ++cnts[x]; // Increment count for candy type x
    }
    std::vector<ll> v; // Vector to store counts of each candy type
    for (std::map<ll, ll>::iterator it = cnts.begin(); it != cnts.end(); it++) {
      v.push_back(it->second); // Store the count of each type
    }
    sort(v.rbegin(), v.rend()); // Sort counts in descending order
    
    ll cur(2e6); // Initialize current max allowed count (start with large value)
    ll sum(0); // Result sum
    for (ll p = 0; p < v.size(); p++) {
      cur = (cur < v[p]) ? cur : v[p]; // Take minimum of current count and available slots
      sum += cur--; // Add current allowed count to sum and decrement
      if (cur <= 0) { // If no more candies can be taken, break
        break;
      }
    }
    printf("%lld\n", sum); // Print result for this query
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/