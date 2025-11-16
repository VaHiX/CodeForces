// Problem: CF 863 C - 1-2-3
// https://codeforces.com/contest/863/problem/C

/*
 * Problem: C. 1-2-3
 * Purpose: Simulate a game between two robots, Alice and Bob, playing "1-2-3" for k rounds.
 *          The game follows specific rules where 3 beats 2, 2 beats 1, and 1 beats 3.
 *          Both robots make moves based on their previous choices. Predict the final scores
 *          after k games using cycle detection and mathematical optimization to handle large k.
 *
 * Algorithms/Techniques:
 *  - Cycle detection using find() to detect repeating states
 *  - Mathematical optimization to compute results for large k using modular arithmetic
 *
 * Time Complexity: O(9 + i) where i is the length of the cycle, which is at most 9.
 * Space Complexity: O(1) as we use fixed-size arrays and variables regardless of k.
 */

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
typedef long long int LL;
const int INF = 1e9;
LL k, x, y, i, l, a[179], b[179]; // a and b arrays store accumulated scores
pair<LL, LL> d[3][3], p[179], *q, f; // d stores the transition rules, p stores pairs of choices

int main() {
  cin >> k >> x >> y;
  x--; // Convert to 0-based indexing
  y--;
  p[0] = {x, y}; // Initial move pair
  a[1] = (3 + x - y) % 3 == 1; // initial score for Alice (1 if Alice wins)
  b[1] = (3 + x - y) % 3 == 2; // initial score for Bob (1 if Bob wins)

  // Read Alice's move rules
  for (i = 0; i < 9; i++) {
    cin >> x;
    d[i / 3][i % 3].first = x - 1; // Convert to 0-based indexing
  }

  // Read Bob's move rules
  for (i = 0; i < 9; i++) {
    cin >> x;
    d[i / 3][i % 3].second = x - 1; // Convert to 0-based indexing
  }

  // Simulate until cycle is detected
  for (i = 1;
       q = find(p, p + i, f = d[p[i - 1].first][p[i - 1].second]), q == p + i;
       i++) {
    a[i + 1] = a[i] + ((3 + f.first - f.second) % 3 == 1); // Update Alice's score
    b[i + 1] = b[i] + ((3 + f.first - f.second) % 3 == 2); // Update Bob's score
    p[i] = f; // Store current state
  }

  l = q - p; // Length of the cycle
  if (k <= i) {
    // If k is less than or equal to the number of simulations done, output directly
    cout << a[k] << " " << b[k];
    return 0;
  }

  k -= l; // Subtract the non-repeating part
  // Use cycle to compute the result
  x = k / (i - l); // Number of full cycles
  cout << x * (a[i] - a[l]) + a[l + k % (i - l)] << " "
       << x * (b[i] - b[l]) + b[l + k % (i - l)] << endl;
}


// https://github.com/VaHiX/CodeForces/