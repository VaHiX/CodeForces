// Problem: CF 1310 A - Recommendations
// https://codeforces.com/contest/1310/problem/A

// Problem: Minimize total time to make all categories have distinct sizes
// Algorithm: Greedy approach with sorting and multiset processing
// Time Complexity: O(n log n) due to sorting and multiset operations
// Space Complexity: O(n) for storing data structures

#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <iterator>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> v(n), t(n);
  std::map<ll, std::multiset<ll>> d; // Maps category size to set of times
  std::map<ll, ll> s;                // Maps category size to total time for that size
  std::set<ll> w;                    // Set of unique category sizes (sorted)
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p]);
    w.insert(v[p]); // Collect all unique category sizes
  }
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &t[p]);
  }
  for (ll p = 0; p < n; p++) {
    d[v[p]].insert(t[p]); // Group times by category size
    s[v[p]] += t[p];      // Sum total time per category size
  }
  std::multiset<ll> carry; // Multiset to hold excess elements waiting for processing
  ll cur(0), res(0);       // cur: current total time, res: final result
  for (std::set<ll>::iterator it = w.begin(); it != w.end(); it++) {
    ll key = *it;
    const std::multiset<ll> mst = d[key];
    res += cur; // Add accumulated time to result
    for (std::multiset<ll>::iterator mit = mst.begin(); mit != mst.end();
         mit++) {
      carry.insert(*mit); // Insert all times into carry
    }
    ll x = *(carry.rbegin()); // Get maximum time in carry (to be removed)
    carry.erase(--carry.end()); // Remove the largest element
    cur += s[key] - x; // Update current time, subtracting max time already used
    while (!carry.empty() && !(w.count(key + 1))) { // While no next size exists in w
      res += cur;
      ll y = *(carry.rbegin()); // Get maximum remaining element
      carry.erase(--carry.end());
      cur -= y; // Reduce current total
      ++key;
    }
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/