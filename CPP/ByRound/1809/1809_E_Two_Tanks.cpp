// Problem: CF 1809 E - Two Tanks
// https://codeforces.com/contest/1809/problem/E

/*
Purpose:
This code solves the problem of simulating water transfer operations between two tanks with given capacities and initial water volumes. 
It precomputes all possible final states of the first tank for every initial state (c, d) and outputs them in a grid format.

Algorithms/Techniques:
- Simulation of tank operations with min function to determine actual water transferred
- Optimization using prefix sums and mathematical derivation to avoid simulating each (c,d) pair individually
- Precomputation and lookup to efficiently answer all queries

Time Complexity: O(a * b + n)
Space Complexity: O(a + n)

Note: The code seems to have an issue with logic in the simulation part.
The current approach attempts to simulate operations but doesn't correctly account for
the interaction between tanks during each operation, especially in how it updates the
transfer values across iterations.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define ll long long
#define ld long double
using namespace std;
string pi = "3141592653589793238462643383279";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tc = 1;
  while (tc--) {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> v(n, 0), h(a + 1, 0), z(a + 1, 0);
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    for (int i = 0; i <= a; ++i)
      h[i] = i;
    int mx = 0;
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i <= a; ++i) {
        h[i] -= v[j]; // Adjusting h[i] for current operation
        z[i] -= v[j]; // Adjusting z[i] for current operation
        h[i] = max(h[i], 0), h[i] = min(h[i], i); // Clamp h[i] to valid range
        z[i] = max(z[i], 0), z[i] = min(z[i], i); // Clamp z[i] to valid range
      }
      if (j != 0)
        v[j] += v[j - 1]; // Update v[j] with cumulative sum
      mx = max(mx, v[j]); // Track maximum value
    }
    for (int i = 0; i <= a; ++i) {
      for (int j = 0; j <= b; ++j) {
        int len = min({a, b, i + j, a + b - i - j}); // Determine length for computation
        int low = max(0, i + j - b); // Compute lower bound
        int dif = i - low; // Compute difference
        if (dif - mx <= 0) 
          cout << low + z[len] << ' '; // Use z for output if condition met
        else
          cout << low + min(dif - mx + z[len], h[len]) << ' '; // Else use h for output
      }
      cout << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/