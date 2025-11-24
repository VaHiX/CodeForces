// Problem: CF 620 C - Pearls in a Row
// https://codeforces.com/contest/620/problem/C

/*
Algorithm: Greedy approach to partition the row of pearls into maximum number of
good segments. A good segment is one that contains at least two pearls of the
same type. We iterate through the pearls and maintain a map to track which types
have been seen in the current segment. Whenever we encounter a type that has
already appeared in the current segment, we finalize the segment and start a new
one.

Time Complexity: O(n), where n is the number of pearls. Each pearl is processed
at most twice (once for insertion, once for detection of duplicate). Space
Complexity: O(n), due to the use of a map to store the types of pearls seen so
far and the vector to store segments.

Techniques:
- Greedy algorithm
- Hash map for tracking types in current segment
- Two-pointer approach
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <utility>
#include <vector>

typedef long long int ll;
#define pp pair<ll, ll>
#define inf 1000000007
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n;
  map<ll, ll> mp; // Map to keep track of types of pearls in current segment
  vector<pp> v;   // Vector to store the segments (start and end indices)
  cin >> n;
  ll a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];

  ll l = 1, r; // l is the start of current segment, r is not used directly but
               // we update it implicitly

  for (i = 0; i < n; i++) {
    if (mp[a[i]] == 0) {
      // If type a[i] has not been seen in current segment, mark it as seen
      mp[a[i]]++;
    } else {
      // If type a[i] has been seen, we found a duplicate -> complete current
      // segment
      v.push_back(
          make_pair(l, i + 1)); // Store the segment from l to i+1 (1-indexed)
      l = i + 2;                // Start of next segment
      mp.erase(mp.begin(), mp.end()); // Clear the map for new segment
    }
  }

  if (v.size() == 0) {
    // No valid segments found (all pearls are unique)
    cout << "-1";
    return 0;
  }

  // Adjust the last segment to extend to the end of the row
  v.back().second = n;

  // Output the number of segments
  cout << v.size() << endl;

  // Output each segment
  for (i = 0; i < v.size(); i++)
    cout << v[i].first << " " << v[i].second << endl;

  return 0;
}

// https://github.com/VaHiX/CodeForces/