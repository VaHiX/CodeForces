// Problem: CF 1585 A - Life of a Flower
// https://codeforces.com/contest/1585/problem/A

/*
A. Life of a Flower
Algorithms/Techniques: Simulation
Time complexity: O(n) per test case
Space complexity: O(1)

The problem simulates the growth of a flower over n days based on watering schedule.
- The flower starts at height 1 cm.
- If not watered for two consecutive days, it dies (return -1).
- If watered on a given day:
  * If previous day was also watered: +5 cm
  * Else: +1 cm
- If not watered on a given day: no growth.

The solution uses a simple loop to simulate each day's effect,
tracking the current height and whether the previous day was watered.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>

using namespace std;
int t, n, k, a, b;
int main() {
  for (scanf("%d", &t); t--; printf("%d\n", k < 0 ? -1 : k))
    for (scanf("%d%d", &n, &b), k = 1 + b; --n;            // Initialize height with 1 + (if first day watered then +1 else +0)
         scanf("%d", &a), a ? (b ? k += 5 : ++k) : (b ? 0 : k = -999), b = a)  // If current day is watered: if previous also watered add 5, otherwise add 1. Else if not watered:
      ;  // Update b to current day's watering status
  exit(0);
}


// https://github.com/VaHiX/codeForces/