// Problem: CF 785 B - Anton and Classes
// https://codeforces.com/contest/785/problem/B

/*
 * Problem: Anton and Classes
 * Purpose: Find the maximum possible distance between a chess class period and a programming class period.
 * Algorithm: 
 *   - Sort chess periods by end time (ascending), and programming periods by start time (ascending).
 *   - Compute the maximum gap between the last chess period and the first programming period.
 *   - Sort programming periods by end time (ascending), and chess periods by start time (ascending).
 *   - Compute the maximum gap between the last programming period and the first chess period.
 *   - Return the maximum of these two gaps.
 * 
 * Time Complexity: O(n log n + m log m)
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

// Comparator to sort pairs by their second element (end time)
bool scmp(std::pair<long, long> a, std::pair<long, long> b) {
  return a.second < b.second;
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> chess(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld %ld", &chess[p].first, &chess[p].second);
  }
  long m;
  scanf("%ld", &m);
  std::vector<std::pair<long, long>> prog(m);
  for (long p = 0; p < m; p++) {
    scanf("%ld %ld", &prog[p].first, &prog[p].second);
  }
  
  // Sort chess periods by end time and prog periods by start time
  sort(chess.begin(), chess.end(), scmp);
  sort(prog.begin(), prog.end());
  
  // Calculate max gap between last chess period and first prog period
  long t1 = prog.back().first - chess[0].second;
  t1 = (t1 > 0) ? t1 : 0; // Ensure non-negative result
  
  // Sort prog periods by end time and chess periods by start time
  sort(prog.begin(), prog.end(), scmp);
  sort(chess.begin(), chess.end());
  
  // Calculate max gap between last prog period and first chess period
  long t2 = chess.back().first - prog[0].second;
  t2 = (t2 > 0) ? t2 : 0; // Ensure non-negative result
  
  // Output the maximum of the two gaps
  printf("%ld\n", ((t1 > t2) ? t1 : t2));
  return 0;
}


// https://github.com/VaHiX/CodeForces/