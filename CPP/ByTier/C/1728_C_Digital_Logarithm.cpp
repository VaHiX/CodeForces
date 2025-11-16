// Problem: CF 1728 C - Digital Logarithm
// https://codeforces.com/contest/1728/problem/C

/*
Purpose:
This code solves the problem of making two arrays similar by applying a "digital logarithm" operation,
which replaces each element with the length of its base-10 representation.
The approach uses a greedy strategy with a map to count and balance the frequency of digit lengths.

Algorithms/Techniques:
- Map-based frequency counting with digit length transformation
- Greedy balancing of frequencies to minimize operations
- Digit length calculation using string conversion

Time Complexity: O(n log M) where n is the number of elements and M is the maximum value (up to 10^9)
Space Complexity: O(n) for the map storage
*/

#include <stdlib.h>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;
map<int, int, greater<int>> mp; // Map to store frequency of numbers and their digit lengths
int T, n, a, ans;

void solve() {
  cin >> n;
  ans = 0;
  mp.clear();
  
  // Read all n numbers from array 'a' and increment their count in map
  for (int i = 0; i < 2 * n; i++)
    cin >> a, mp[a] += i < n ? 1 : -1;
  
  // For each entry in the map, transform the key to its digit length and accumulate counts
  for (auto k : mp)
    mp[to_string(k.first).length()] += k.second, ans += abs(k.second);
  
  cout << ans << '\n';
}

int main() {
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/