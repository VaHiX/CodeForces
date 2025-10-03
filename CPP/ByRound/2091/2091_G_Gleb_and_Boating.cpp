// Problem: CF 2091 G - Gleb and Boating
// https://codeforces.com/contest/2091/problem/G

/*
G. Gleb and Boating
Problem Description:
Gleb rows a kayak from point 0 to point s, where each paddle stroke moves him forward or backward depending on his current power.
- Initial power is k.
- Each stroke moves distance equal to current power.
- Turning around decreases power by 1 (but never goes below 1).
- Cannot turn twice in a row.
- Cannot turn immediately after start.

Algorithm:
The solution uses a greedy approach to minimize the number of turns needed to reach point s,
by adjusting the paddle strokes and power consumption efficiently.
It simulates the motion while trying to keep power as high as possible when reaching destination.

Time Complexity: O(log s)
Space Complexity: O(1)

*/

#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  long long n, tam;
  while (t--) {
    cin >> n >> tam;
    long long i, f;
    i = n % tam, f = n % tam; // Initialize variables to simulate movement
    while (true) {
      if (i == 0)
        break;
      tam = tam - 2; // Reduce power due to turn
      if (tam == 0 || tam == 1) { // If power becomes 0 or 1, stop
        tam = 1;
        break;
      }
      i = (i + 1); // Update current position
      f = f + (n - f) / (tam + 1) + (n - (f)) / (tam + 2) - 1; 
      // Compute new final position based on remaining distance and power
      long long dif = f - i;
      i = i % tam;
      if (i == 0)
        break;
      if (i + dif >= tam)
        break;
      f = f % tam;
    }
    cout << tam << endl; // Output resulting maximum power
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/