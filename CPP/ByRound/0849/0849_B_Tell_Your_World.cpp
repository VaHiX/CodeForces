// Problem: CF 849 B - Tell Your World
// https://codeforces.com/contest/849/problem/B

/*
 * Problem: B. Tell Your World
 * 
 * Algorithm: 
 *   - The key idea is to check if we can partition the points into two parallel lines.
 *   - For each possible slope (based on pairs of points), we compute the y-intercept for each point 
 *     using the line equation y = mx + b => b = y - mx.
 *   - If all points on one line give the same y-intercept, and all points on the other line give 
 *     another y-intercept, and there are exactly 2 distinct intercepts, then it's a valid partition.
 *   - We try three possible slopes based on the first few points to cover cases where points are 
 *     aligned in some pattern.
 * 
 * Time Complexity: O(n) - We iterate through the points a constant number of times (3).
 * Space Complexity: O(n) - We use a set to store up to n y-intercepts.
 * 
 * Techniques:
 *   - Mathematical line equation manipulation (y = mx + b)
 *   - Set for deduplication of y-intercepts
 *   - Early termination through logical OR
 */

#include <cstdio>
#include <set>
#include <vector>
bool check(std::vector<long> a, double slope) {
  std::set<double> s;
  for (long p = 1; p < a.size(); p++) {
    // Calculate y-intercept for each point using line equation: b = y - mx
    s.insert(a[p] - slope * p);
  }
  // If there are exactly 2 distinct y-intercepts, it means we can split the points into 2 lines
  return (s.size() == 2);
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1);  // 1-indexed array to store y-coordinates
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  // Try three possible slopes to see if any leads to a valid partition
  bool res = check(a, a[2] - a[1]) || check(a, a[3] - a[2]) ||
             check(a, (a[3] - a[1]) / 2.0);
  puts(res ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/