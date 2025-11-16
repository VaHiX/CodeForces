// Problem: CF 2169 D1 - Removal of a Sequence (Easy Version)
// https://codeforces.com/contest/2169/problem/D1

/*
Code Purpose:
This program solves the problem of determining the k-th element in a sequence after performing x removal operations.
Each operation removes elements at positions y, 2*y, 3*y, ..., m*y where m*y <= current sequence length.
The algorithm simulates the reverse process to find the k-th element efficiently without constructing the full sequence.

Algorithms/Techniques:
- Simulation with reverse thinking: For each removal step, we compute how the position of an element changes.
- Mathematical manipulation to avoid simulating all removals step-by-step.

Time Complexity: O(x), where x is the number of operations; each operation involves constant time math.
Space Complexity: O(1), only using a few variables for computation.

*/
#include <iostream>

using namespace std;
#define int long long
signed main() {
  int t;
  cin >> t;
  while (t--) {
    int x, y, z;
    cin >> x >> y >> z;
    if (y == 1) {
      cout << -1 << endl;
      continue;
    }
    int curr = z;  // Start from the k-th position and trace back
    while (x--) {
      // Compute the new position after one removal operation
      // curr += y * ((curr - 1) / (y - 1)) - (y - 1) * ((curr - 1) / (y - 1));
      // Simplify above line to:
      curr += ((curr - 1) / (y - 1));  // This line effectively updates position
    }
    cout << ((curr > 1e12) ? -1 : curr) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/