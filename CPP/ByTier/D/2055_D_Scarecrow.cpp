// Problem: CF 2055 D - Scarecrow
// https://codeforces.com/contest/2055/problem/D

/*
D. Scarecrow
Algorithms/Techniques: Greedy, Simulation, Two Pointers

Time Complexity: O(n) amortized per test case, where n is the number of scarecrows.
Space Complexity: O(n) for storing the positions of scarecrows.

The problem involves a crow moving along a number line and teleporting when too close to scarecrows.
Scarecrows are allowed to move optimally to delay the crow's movement as much as possible,
while maintaining the constraint that the crow must stay at least distance k ahead of
the nearest scarecrow positioned at or before it.

The simulation tracks:
- `t`: total time elapsed
- `now`: current position of the crow
- For each scarecrow, we calculate when and how it affects the crow's path,
  adjusting for the time taken for scarecrows to move and for teleportation.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, k, l, a[200200], t, now, ti[200200];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k >> l;
    k <<= 1;       // Double k for internal calculations
    l <<= 1;       // Double l as required by output format
    t = 0;         // Initialize total time
    now = 0;       // Initialize crow's position
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      a[i] <<= 1;  // Double positions for internal calculations
    }
    t = a[1];      // Start time with first scarecrow's position
    now = k;       // Initial position of crow, ensuring it's at least k ahead
    for (int i = 2; i <= n; i++) {
      if (now <= a[i] + t && now >= a[i] - t) {
        // Crow is within teleportation range, advance time by k
        now += k;
      } else if (now < a[i] - t) {
        // Crow is too far behind, adjust time and position to catch up
        int u = (a[i] - t - now) >> 1;  // Calculate half of the gap
        t += u;   // Adjust total time
        now += u; // Adjust crow's position
        now += k; // Add the required k distance back
      } else {
        // Crow is ahead, set new position to be at least k ahead of current scarecrow
        now = max(now, a[i] + t + k);
      }
    }
    cout << t + max(0, l - now) << "\n";  // Final time output with l adjustment
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/