// Problem: CF 1450 B - Balls of Steel
// https://codeforces.com/contest/1450/problem/B

/*
B. Balls of Steel
Algorithm: For each point, check if all other points are within Manhattan distance k.
If so, one operation is enough. If no such point exists, return -1.
Time Complexity: O(n^2), where n is the number of points.
Space Complexity: O(n), for storing the points.

Input:
- t test cases
- For each case: n (number of balls), k (attract power)
- Then n lines with coordinates of balls

Output:
- Minimum operations to move all balls to same position, or -1 if impossible
*/
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::pair<long, long>> f(n); // Store coordinates of balls
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &f[p].first, &f[p].second); // Read ball coordinates
    }
    bool res(false); // Flag to store result
    for (long p = 0; p < n; p++) { // For each ball as potential center
      bool cur(true); // Check if we can move all balls to this point
      for (long q = 0; q < n; q++) { // Check distance to all other balls
        long dx = f[p].first - f[q].first;
        if (dx < 0) {
          dx = -dx; // Manhattan x distance
        }
        long dy = f[p].second - f[q].second;
        if (dy < 0) {
          dy = -dy; // Manhattan y distance
        }
        if (dx + dy > k) { // If distance exceeds k
          cur = false; // Not valid center point
          break;
        }
      }
      if (cur) { // If all points are within k distance
        res = true; // Found solution
        break;
      }
    }
    printf("%d\n", res ? 1 : -1); // Print 1 if solvable, otherwise -1
  }
}


// https://github.com/VaHiX/codeForces/