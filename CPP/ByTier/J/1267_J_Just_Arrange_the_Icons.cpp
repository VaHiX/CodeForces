// Problem: CF 1267 J - Just Arrange the Icons
// https://codeforces.com/contest/1267/problem/J

/*
J. Just Arrange the Icons

Algorithms/Techniques:
- Count frequency of each category
- Map frequencies to their counts
- Try different screen sizes (d) from 1 to max frequency + 1
- For each screen size d, compute minimal screens needed by rounding up
  frequencies to fit in screen size
- Greedy approach to minimize total number of screens

Time Complexity: O(n log n) per test case due to map operations and iteration over frequencies
Space Complexity: O(n) for storing counts and map

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
using LL = long long;
constexpr int N = 1e5 + 5;

void solve() {
  int n;
  cin >> n;
  vector<int> cnt(n + 1); // Count of each category
  for (int i = 1; i <= n; i++) {
    int c;
    cin >> c;
    cnt[c]++;
  }
  map<int, int> mp; // Map frequency -> count of how many categories have this frequency
  for (int x : cnt)
    if (x)
      mp[x]++;
  
  int Size = mp.begin()->first; // Get the smallest frequency
  int ans = n;                 // Initialize with maximum possible screens (all single icons)
  Size++;                      // Increment to allow iteration up to including max freq
  for (int d = 1; d <= Size; d++) { // Try all reasonable screen sizes
    bool ok = 1;
    int T = 0;
    for (auto &[a, b] : mp) { // For each frequency a with count b
      int q = (a + d - 1) / d; // Compute minimum screens needed for this freq
      if (a < q * (d - 1))     // Check if this fits the constraint (at least d-1 per screen)
        ok = 0;
      else
        T += q * b; // Add total screens needed for this frequency group
    }
    if (ok) {
      ans = min(ans, T); // Update minimum screens
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/