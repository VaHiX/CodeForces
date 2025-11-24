// Problem: CF 1771 B - Hossam and Friends
// https://codeforces.com/contest/1771/problem/B

/*
Algorithm: Sliding window / Interval merging
Time Complexity: O(m + n), where m is the number of pairs and n is the number of friends.
Space Complexity: O(n), for storing the map of intervals.

The idea is to find all the intervals where friends are not on good terms.
We then calculate how many subsegments are good by subtracting invalid subsegments from total.
We use a map to store the rightmost invalid position for each left position.
We then iterate from left to right and keep track of the furthest invalid point seen so far.
For each position i, the number of good subsegments ending at i is (i - max_invalid_position).
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

#define ll long long
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    ll n;
    ll m;
    cin >> n >> m;
    map<ll, ll> po; // Map to store the maximum invalid index for each starting index
    for (ll i = 1; i <= m; i++) {
      ll q, w;
      cin >> q >> w;
      if (q < w)
        swap(q, w); // Ensure q >= w to normalize the pair
      po[q] = max(po[q], w); // Update the maximum invalid index for q
    }
    ll ans; // Final answer to be calculated
    ll qw; // Track the furthest invalid index
    ans = 0;
    qw = 0;
    for (ll i = 1; i <= n; i++) {
      qw = max(qw, po[i]); // Update the furthest invalid index seen so far
      ans = ans + i - qw; // Add number of good subsegments ending at i
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/