// Problem: CF 493 C - Vasya and Basketball
// https://codeforces.com/contest/493/problem/C

/*
 * Problem: Vasya and Basketball
 * 
 * Algorithm: 
 *   - We are given two teams' throw distances. Each throw is worth 2 or 3 points
 *     depending on whether the distance is <= d or > d, where d is a chosen threshold.
 *   - We want to maximize the difference (first_team_points - second_team_points).
 *   - Strategy:
 *     - Initially assign all throws 3 points (assuming d = 0).
 *     - For each unique distance in sorted order, decrease the point count
 *       for all throws at that distance (either 2 or 3 points become 2 for first team).
 *     - Keep track of maximum difference and corresponding scores.
 *
 * Time Complexity: O((n + m) log(n + m)) due to sorting, where n, m are sizes of teams.
 * Space Complexity: O(n + m) for storing the scores.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long long> total(2); // total[0] -> first team total, total[1] -> second team total
  std::vector<std::pair<long, long>> score; // pair of (distance, team_id)
  
  // Read first team's throws
  for (long p = 0; p < n; p++) {
    long dist;
    scanf("%ld", &dist);
    score.push_back(std::pair<long, long>(dist, 0)); // team 0
  }
  
  long m;
  scanf("%ld\n", &m);
  // Read second team's throws
  for (long p = 0; p < m; p++) {
    long dist;
    scanf("%ld", &dist);
    score.push_back(std::pair<long, long>(dist, 1)); // team 1
  }
  
  // Initially give 3 points to all throws
  total[0] = 3 * n;
  total[1] = 3 * m;
  
  // Sort by distance
  sort(score.begin(), score.end());
  
  // Initial difference
  long long diff = total[0] - total[1];
  long long first(total[0]), second(total[1]); // best scores found so far
  
  // Iterate through each unique distance
  for (long p = 0; p < score.size(); p++) {
    // Decrease total points for throws at (or before) current distance threshold
    --total[score[p].second];
    
    // Check if new max difference is achieved
    if (total[0] - total[1] > diff) {
      diff = total[0] - total[1];
      first = total[0];
      second = total[1];
    }
  }
  
  printf("%lld:%lld\n", first, second);
  return 0;
}


// https://github.com/VaHiX/CodeForces/