// Problem: CF 660 D - Number of Parallelograms
// https://codeforces.com/contest/660/problem/D

/*
 * Problem: Number of Parallelograms
 * 
 * Algorithm/Technique:
 * - Use the property that in a parallelogram, the diagonals bisect each other.
 *   Hence, for any two points, their midpoint determines a unique vector.
 * - For each pair of points, compute the vector between them and store the count
 *   of how many times each vector occurs.
 * - For each vector that occurs 'k' times, the number of parallelograms formed is
 *   C(k, 2) = k * (k - 1) / 2.
 * - Since each parallelogram is counted twice (once for each diagonal),
 *   we divide the final result by 2.
 * 
 * Time Complexity: O(n^2 * log n) due to the map operations and nested loops.
 * Space Complexity: O(n^2) for storing the vectors in the map.
 */

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> x(n), y(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld %ld", &x[p], &y[p]);
  }
  std::map<std::pair<long, long>, long> m;
  for (long a = 0; a < n; a++) {
    for (long b = 0; b < a; b++) {
      long dx = x[a] - x[b];
      long dy = y[a] - y[b];
      // Ensure the vector is canonical (positive or positive y)
      if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
      }
      std::pair<long, long> v = std::make_pair(dx, dy);
      if (m.count(v) <= 0) {
        m[v] = 0;
      }
      ++m[v];
    }
  }
  long total(0);
  for (std::map<std::pair<long, long>, long>::iterator it = m.begin();
       it != m.end(); ++it) {
    long same = it->second;
    total += same * (same - 1) / 2;
  }
  printf("%ld\n", total / 2);
  return 0;
}


// https://github.com/VaHiX/CodeForces/