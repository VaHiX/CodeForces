// Problem: CF 1140 C - Playlist
// https://codeforces.com/contest/1140/problem/C

/*
C. Playlist
Algorithm: Greedy + Multiset
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem is to select at most k songs from a playlist such that the pleasure 
(total length * minimum beauty) is maximized. 

Approach:
1. Sort songs in descending order of beauty (b_i). This ensures we consider 
   songs with higher beauty first, allowing us to maintain a valid set of at most k songs.
2. Use a multiset to keep track of the durations of selected songs.
3. For each song in sorted order:
   - Add its duration to the running total.
   - Compute the current pleasure as (total duration) * (current song's beauty).
   - If we've selected more than k songs, remove the one with smallest duration.
4. Track and return the maximum pleasure encountered.

This greedy approach works because after sorting by beauty, we always process 
songs in order of decreasing beauty. When considering a new song, if it can be 
included (i.e., we're under k songs), we compute an updated pleasure. If we exceed k,
we remove the smallest duration song to maintain at most k songs.
*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<std::pair<ll, ll>> v(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld %lld", &v[p].second, &v[p].first); // Read duration and beauty
  }
  sort(v.rbegin(), v.rend()); // Sort in descending order by beauty
  std::multiset<ll> s;
  ll duration(0), mxp(0);
  for (ll p = 0; p < n; p++) {
    ll tst = (duration + v[p].second) * v[p].first; // Compute current pleasure
    mxp = (mxp > tst ? mxp : tst); // Update maximum pleasure
    duration += v[p].second; // Add song's duration to total
    s.insert(v[p].second); // Insert song's duration into multiset
    while (s.size() >= k) { // If we have more than k songs
      duration -= *s.begin(); // Remove the one with smallest duration
      s.erase(s.begin()); // Erase from multiset
    }
  }
  printf("%lld\n", mxp);
  return 0;
}


// https://github.com/VaHiX/codeForces/