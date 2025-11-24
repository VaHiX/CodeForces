// Problem: CF 2068 C - Ads
// https://codeforces.com/contest/2068/problem/C

/*
C. Ads
Algorithms/Techniques: Greedy algorithm with sorting and two-pointer technique.
Time Complexity: O(n log n + n) per test case due to sorting and linear traversal.
Space Complexity: O(n) for the array and auxiliary arrays.

The problem is about minimizing the number of ads shown when watching videos in an optimal order.
Two conditions trigger an ad:
1. After every 3 videos.
2. After k minutes since last ad.

Strategy:
- Sort the videos by duration.
- Use greedy two-pointer approach to pair videos optimally.
- Avoid unnecessary ad triggers by carefully choosing video order.
*/

#include <string.h>
#include <algorithm>
#include <iostream>

const int N = 1e6 + 5;
int n, t, a[N];
bool vis[N];

void solve() {
  std::cin >> n >> t; // Read number of videos and threshold k
  for (int i = 1; i <= n; i++)
    std::cin >> a[i]; // Read durations of videos
  int ans = 0;
  std::sort(a + 1, a + n + 1), memset(vis + 1, false, sizeof(bool) * n); // Sort and reset visited array
  for (int i = 1, j = n, k = n; i <= n; i++, j--) // Two pointers from start and end
    if (!vis[i]) { // If not yet paired
      for (; i < j && (a[i] + a[j] >= t || vis[j]); j--) // Move pointer j backward until valid pair or skipped
        ;
      vis[i] = true, ans++; // Mark current video as used and increment ad count
      if (i < j && !vis[j] && a[i] + a[j] < t) // If we found a valid pair
        vis[j] = true; // Mark paired video as used
      if (a[i] < t) { // If this video is less than threshold k
        for (; i < k && vis[k]; k--) // Move pointer k backward until unvisited
          ;
        if (i < k && !vis[k]) // If valid and unvisited
          vis[k] = true; // Mark as used
      }
    }
  std::cout << ans - 1 << "\n"; // Subtract one because initial ad is already counted
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr),
      std::cout.tie(nullptr);
  int T;
  std::cin >> T;
  for (; T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/