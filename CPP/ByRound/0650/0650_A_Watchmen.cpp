// Problem: CF 650 A - Watchmen
// https://codeforces.com/contest/650/problem/A

#include <stdint.h>
#include <iostream>
#include <map>
#include <utility>

/*
 * Problem: Count pairs of watchmen where Manhattan distance equals Euclidean distance.
 * 
 * Algorithm:
 * - For each point (x, y), we maintain counts of how many times:
 *   - x-coordinate has appeared (countX)
 *   - y-coordinate has appeared (countY)
 *   - point (x, y) has appeared (countXY)
 * - When processing a point:
 *   - Add count of same x-coordinate to pairs (these form Manhattan = Euclidean pairs)
 *   - Add count of same y-coordinate to pairs (these form Manhattan = Euclidean pairs)
 *   - Subtract count of same (x, y) point to avoid overcounting (since we are looking for i < j)
 *   - Update all counters
 * 
 * Time Complexity: O(n log n) due to map operations (log n per insertion/query)
 * Space Complexity: O(n) for storing counts in maps
 */
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::map<long, long> countX;
  std::map<long, long> countY;
  std::map<std::pair<long, long>, long> countXY;
  int64_t pairs(0);
  while (n--) {
    long x, y;
    std::cin >> x >> y;
    if (countX.count(x) > 0) {
      pairs += countX[x];  // Add pairs with same x-coordinate
      ++countX[x];
    } else {
      countX[x] = 1;
    }
    if (countY.count(y) > 0) {
      pairs += countY[y];  // Add pairs with same y-coordinate
      ++countY[y];
    } else {
      countY[y] = 1;
    }
    std::pair<long, long> xy = std::make_pair(x, y);
    if (countXY.count(xy) > 0) {
      pairs -= countXY[xy];  // Remove overcounted pairs with same point
      ++countXY[xy];
    } else {
      countXY[xy] = 1;
    }
  }
  std::cout << pairs << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/