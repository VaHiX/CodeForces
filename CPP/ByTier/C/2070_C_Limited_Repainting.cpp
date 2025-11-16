// Problem: CF 2070 C - Limited Repainting
// https://codeforces.com/contest/2070/problem/C

/*
 * C. Limited Repainting
 *
 * Purpose:
 *   Given a strip of n cells, each initially red, and a target coloring (string s),
 *   determine the minimum possible penalty when performing at most k repainting
 *   operations. Each operation repaints a segment of consecutive cells to blue.
 *   Penalty for wrong color is given by array a, and final penalty is maximum
 *   among all incorrectly colored cells.
 *
 * Algorithms/Techniques:
 *   - Binary search on the answer (penalty value)
 *   - Greedy validation: For a fixed penalty threshold, check if it's possible
 *     to achieve that penalty with at most k operations by scanning the string
 *     and greedily using segments to correct wrong colors.
 *
 * Time Complexity:
 *   O(n * log(max_a)) where max_a <= 1e9, and n is up to 3 * 10^5 per test case.
 *   For each binary search iteration, we do one pass through the string: O(n).
 *   Binary search depth: O(log(max_a)).
 *
 * Space Complexity:
 *   O(n) for storing the input string and penalties vector.
 */

#include <iostream>
#include <vector>
#include <string>

bool check(const std::vector<long> &w, const std::string &s, long k,
           long penalty) {
  bool paint(false); // Tracks if we are currently painting a segment
  long cnt(0);       // Number of operations used
  for (long p = 0; p < w.size(); p++) {
    // Skip cells with penalties less than the current test penalty (they don't affect result)
    if (w[p] < penalty) {
      continue;
    }
    // If current cell should be blue ('B') and we're not painting yet, start new segment
    if (s[p] == 'B' && !paint) {
      paint = true;
      ++cnt;
    }
    // If current cell should be red ('R') and we are painting, end segment
    if (s[p] == 'R' && paint) {
      paint = false;
    }
    // Early exit if we've used more than k operations
    if (cnt > k) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    long left(0), right(1e9 + 7), res(0);
    // Binary search on the penalty value
    while (left <= right) {
      long mid = (left + right) / 2;
      if (check(v, s, k, mid)) {
        right = mid - 1;   // Try smaller penalty
      } else {
        res = mid;         // This penalty works, save it as a candidate
        left = mid + 1;    // Try higher penalty
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/