// Problem: CF 1839 B - Lamps
// https://codeforces.com/contest/1839/problem/B

/*
B. Lamps
Algorithm: Greedy with sorting and simulation
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing lamp data

Problem Description:
We have n lamps, each with parameters a_i and b_i.
- Turning on lamp i gives b_i points
- After turning on a lamp, all lamps j such that a_j <= current number of turned-on lamps break
- Goal is to maximize total points

Approach:
1. Sort lamps by a_i ascending, then by b_i descending to prioritize higher values when a_i are same
2. Greedily turn on lamps while simulating the breaking process
3. Use a greedy strategy: always prefer lamps with higher b_i that don't break immediately
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

// Custom comparator: sort by a_i ascending, then by b_i descending
bool cmp(std::pair<ll, ll> a, std::pair<ll, ll> b) {
  if (a.first != b.first) {
    return a.first < b.first; // Sort by first element ascending
  }
  return a.second > b.second; // If first equal, sort by second descending
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &v[p].first, &v[p].second); // Read a_i and b_i
    }
    sort(v.begin(), v.end(), cmp); // Sort according to custom comparator
    
    ll idx(0), cnt(0), total(0);
    for (ll p = 0; p < n; p++) {
      if (p < idx) {
        continue; // Skip already processed lamps
      }
      total += v[p].second; // Turn on lamp p and add its points
      ++cnt;
      while (idx < n && v[idx].first <= cnt) { // Update idx to skip broken lamps
        ++idx;
      }
      cnt = p - idx + 1;
      cnt = (cnt > 0 ? cnt : 0);
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/