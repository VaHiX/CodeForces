// Problem: CF 978 F - Mentors
// https://codeforces.com/contest/978/problem/F

/*
Algorithm: 
- We use sorting and prefix sum technique to count valid mentors efficiently.
- For each programmer, we initially count how many programmers with lower skill levels are in quarrel with them.
- Then, we sort the programmers by skill level and use a prefix sum approach to calculate the final result.

Time Complexity: O(n log n) due to sorting step, where n is the number of programmers.
Space Complexity: O(n) for storing the skill levels, indices, and temporary array.

The key idea is to preprocess quarrels, then use sorted order to efficiently compute mentor counts.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<std::pair<ll, ll>> r(n);  // Store {skill, index}
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &r[p].first);
    r[p].second = p;
  }
  std::vector<ll> t(n, 0);  // Initialize result array with zeros
  for (long p = 0; p < k; p++) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    --x;
    --y;
    // If x has lower skill than y, decrement y's count (y can't be mentored by x)
    if (r[x].first < r[y].first) {
      --t[y];
    } else if (r[y].first < r[x].first) {
      // If y has lower skill than x, decrement x's count (x can't be mentored by y)
      --t[x];
    }
  }
  sort(r.begin(), r.end());  // Sort by skill level
  ll prev(0);  // Keep track of the starting index for the current skill level group
  for (ll p = 1; p < n; p++) {
    if (r[p].first > r[p - 1].first) {
      prev = p;  // Update the start index when next skill level is greater
    }
    ll w = r[p].second;  // Get actual index of the programmer
    t[w] += prev;  // Add number of valid mentors from previous levels
  }
  for (ll p = 0; p < n; p++) {
    printf("%lld ", t[p]);
  };
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/