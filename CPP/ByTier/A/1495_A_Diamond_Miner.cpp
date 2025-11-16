// Problem: CF 1495 A - Diamond Miner
// https://codeforces.com/contest/1495/problem/A

/*
Purpose: 
This code solves the Diamond Miner problem where n miners on the y-axis must be paired with n diamond mines on the x-axis to minimize total energy consumption. Each miner uses a hook to mine exactly one diamond, and the energy cost is the Euclidean distance between the miner and the diamond.

Algorithm:
- The problem is essentially a pairing problem where we want to minimize sum of Euclidean distances.
- Since all miners are on the y-axis and all diamonds are on the x-axis, the cost to pair miner at (0, b) with diamond at (a, 0) is sqrt(a^2 + b^2).
- By sorting the x-coordinates (diamonds) and y-coordinates (miners), the optimal assignment is to pair the smallest x with the smallest y, and so on (greedy optimal pairing).
- Time Complexity: O(n log n) due to sorting
- Space Complexity: O(n) for storing the coordinates

Techniques:
- Greedy pairing after sorting
- Euclidean distance calculation
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<double> v, w; // v stores x-coordinates of diamonds, w stores y-coordinates of miners
    for (long p = 0; p < 2 * n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      if (x < 0) {
        x = -x;
      }; // Ensure x is positive for diamond (since on x-axis)
      if (y < 0) {
        y = -y;
      } // Ensure y is positive for miner (since on y-axis)
      if (x) {
        v.push_back(x); // If x is non-zero, it's a diamond mine at (x, 0)
      } else {
        w.push_back(y); // If y is non-zero, it's a miner at (0, y)
      }
    }
    sort(v.begin(), v.end()); // Sort diamonds by x-coordinate
    sort(w.begin(), w.end()); // Sort miners by y-coordinate
    double total(0);
    for (long p = 0; p < n; p++) {
      total += sqrt(v[p] * v[p] + w[p] * w[p]); // Pair each sorted x with sorted y, accumulate energy
    }
    printf("%.11lf\n", total);
  }
}


// https://github.com/VaHiX/CodeForces/