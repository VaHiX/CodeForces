// Problem: CF 994 B - Knights of a Polygonal Table
// https://codeforces.com/contest/994/problem/B

/*
Purpose: 
This program determines the maximum number of coins each knight can accumulate by killing other knights,
given that a knight can only kill knights with less power and at most k other knights.
It uses a sorting approach combined with a multiset to efficiently track the largest coins that can be stolen.

Algorithms/Techniques:
- Sorting knights by power
- Using a multiset to maintain up to k largest coin values from previous knights
- Prefix sum technique to calculate accumulated coins for each knight

Time Complexity: O(n log n)
Space Complexity: O(n)

*/
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

typedef long long ll;
struct knight {
  ll power, wealth, order;
};
bool knightCompare(knight a, knight b) { return a.power < b.power; }
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<knight> v(n);
  for (ll p = 0; p < n; p++) {
    v[p].order = p;
  }
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p].power);
  }
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p].wealth);
  }
  sort(v.begin(), v.end(), knightCompare); // Sort knights by power
  std::multiset<ll> ms; // Maintain a multiset of coin values for efficient max selection
  ll sum(0);
  std::vector<ll> r(n, 0); // Result array to store maximum coins for each knight
  r[v[0].order] = v[0].wealth; // First knight (weakest) has no one to kill, so initial coins only
  for (long p = 1; p < n; p++) {
    if (v[p - 1].power < v[p].power) {
      ms.insert(v[p - 1].wealth); // Insert the wealth of the previous knight (weaker)
      sum += v[p - 1].wealth; // Add to sum of coins available to steal
      if (ms.size() > k) {
        sum -= *ms.begin(); // Remove smallest value in multiset (least valuable coin to steal)
        ms.erase(ms.begin()); // Remove the smallest element
      }
    }
    r[v[p].order] = sum + v[p].wealth; // Store max coins for current knight
  }
  for (long p = 0; p < n; p++) {
    printf("%lld ", r[p]); // Print result for each knight
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/