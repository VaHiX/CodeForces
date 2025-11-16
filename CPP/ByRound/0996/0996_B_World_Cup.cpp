// Problem: CF 996 B - World Cup
// https://codeforces.com/contest/996/problem/B

/*
 * Code purpose: Determine the entrance through which Allen will enter the fan zone,
 *               based on a queue rotation strategy where Allen moves to the next queue
 *               each minute if he is not the first in line.
 *
 * Algorithms/Techniques: Mathematical approach to calculate the time Allen would take
 *                        to reach the front of each queue, without simulating the full process.
 *
 * Time Complexity: O(n) - Single pass through the array of entrances.
 * Space Complexity: O(n) - For storing the queue lengths.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long mint(1e9 + 7), entry(-1);
  for (long p = 0; p < n; p++) {
    // Calculate the time (in minutes) when Allen will be at the front of queue p
    // This uses modular arithmetic and arithmetic progression to avoid simulation.
    long cand = p + n * ((a[p] - p + (n - 1)) / n);
    if (cand < mint) {
      mint = cand;
      entry = p;
    }
  }
  printf("%ld\n", 1 + entry);  // Output 1-indexed entrance number
  return 0;
}


// https://github.com/VaHiX/CodeForces/