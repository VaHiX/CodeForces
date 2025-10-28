// Problem: CF 1889 C2 - Doremy's Drying Plan (Hard Version)
// https://codeforces.com/contest/1889/problem/C2

/*
 * Problem: C2. Doremy's Drying Plan (Hard Version)
 * Algorithm: Dynamic Programming with Segment Optimization
 * Time Complexity: O(m * k^2)
 * Space Complexity: O(n * k + m * k)
 *
 * Key approach:
 * 1. Use prefix sums to count how many days it rains in each city.
 * 2. For each possible number of days (0 to k) that are freed from rain,
 *    compute the maximum number of dry cities.
 * 3. Use dynamic programming with optimization to efficiently track
 *    best results for different combinations of freed days.
 */

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const int maxn = 200005, maxk = 11;
int rain[maxn]; // rain[i] - number of days it rains in city i
int cnt[maxk][maxn]; // cnt[j][i] - number of cities that get rained j times up to city i
pair<int, int> segm[maxn]; // segments of rain days [l, r]
pair<int, int> maxr[maxk]; // maxr[j] - stores (end, index) of latest segment that covers j+1 days of rain
int best[maxk][maxk]; // best[j][h] - max dry cities for j freed days with h days in segment
int curr[maxk][maxk]; // curr[j][h] - current DP result for j freed days and h segment
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i <= n; i++) {
      rain[i] = 0;
    }
    for (int i = 0; i < m; i++) {
      cin >> segm[i].first >> segm[i].second;
      rain[segm[i].first]++;
      rain[segm[i].second + 1]--;
    }
    // Compute prefix sums of rain counts for each city
    for (int i = 1; i <= n; i++) {
      rain[i] += rain[i - 1];
      for (int j = 0; j <= k; j++) {
        cnt[j][i] = cnt[j][i - 1];
        if (rain[i] == j)
          cnt[j][i]++;
      }
    }
    // Sort segments by their end points
    sort(segm, segm + m);
    int ans = 0;
    // Initialize best values
    for (int i = 0; i <= k; i++) {
      maxr[i] = {-1, -1};
      best[i][0] = cnt[0][n];
    }
    for (int i = 0; i <= k; i++) {
      for (int j = 0; j <= k; j++) {
        curr[i][j] = 0;
      }
    }
    // Process each segment in order
    for (int i = 0; i < m; i++) {
      // Count how many cities would be freed by this segment
      int freed = cnt[1][segm[i].second] - cnt[1][segm[i].first - 1];
      // Update current DP values for 1 freed day
      for (int j = 1; j <= k; j++) {
        curr[j][0] = freed + best[j - 1][0];
      }
      // Update DP values for more freed days using previously computed values
      for (int j = 1; j < k; j++) {
        if (maxr[j].second == -1)
          break;
        freed += max(0, cnt[j + 1][min(segm[i].second, maxr[j].first)] -
                            cnt[j + 1][segm[i].first - 1]);
        for (int h = j + 1; h <= k; h++) {
          curr[h][j] = freed + best[h - 1][j];
        }
      }
      // Propagate best values
      for (int j = 1; j <= k; j++) {
        for (int h = j - 1; h >= 0; h--) {
          curr[j][h] = max(curr[j][h], curr[j][h + 1]);
          best[j][h] = max(best[j][h], curr[j][h]);
        }
      }
      // Update maxr and propagate best values when a new segment covers
      for (int j = 1; j < k; j++) {
        if (segm[i].second > maxr[j].first) {
          for (int h = k - 1; h > j; h--)
            maxr[h] = maxr[h - 1];
          maxr[j] = {segm[i].second, i};
          for (int h = j; h < k; h++) {
            for (int g = h; g <= k; g++) {
              best[g][h] = curr[g][h - 1];
            }
          }
          break;
        }
      }
    }
    cout << best[k][0] << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/