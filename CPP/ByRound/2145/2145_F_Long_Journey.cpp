// Problem: CF 2145 F - Long Journey
// https://codeforces.com/contest/2145/problem/F

/*
F. Long Journey
Algorithms/Techniques: Cycle detection in a deterministic automaton, BFS with cycle optimization
Time Complexity: O(L * n + log(to)) where L is the LCM of all a[i], n is the number of rules, to is the target position
Space Complexity: O(L * n) for storing states and transitions

The problem simulates a chip moving along a strip of cells under trap activation rules.
Each turn, the chip either moves or stays in place. Traps are activated at certain turn numbers based on modular arithmetic.
We use BFS with cycle detection to efficiently compute minimum turns to reach cell m.

The state is defined by (position, turn_number % n) where n is number of rules.
Cycle detection helps when we detect repeated states and allows for fast computation using modular arithmetic.
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
const int N = 12, B = 3000;
int n, s, a[N], b[N];
ll to;
void work() {
  cin >> n >> to;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  int l = 1;
  for (int i = 0; i < n; i++)
    l = lcm(l, a[i]); // Compute LCM of all moduli
  vector<int> v(l * n + 1, 1e9), w(n, -1); // v stores min turns to reach each state, w tracks visited turn_mods
  v[0] = 0;
  w[0] = 0;
  int x = 0, i = 0, s, e, d; // x tracks current position in flattened space
  while (x < l * n && x < to) {
    if ((x + 1) % a[i % n] != b[i % n]) // Check if trap would activate in current cell at turn (i+1)
      x++;
    i++;
    v[x] = min(v[x], i); // Update min turns to reach this state
    if (x % l == 0) { // Check for cycle when we are at a multiple of LCM
      if (w[i % n] != -1 && w[i % n] != x) { // If same turn_mod was seen with same position
        s = w[i % n], e = x;
        d = (i - v[s]) / n * n; // Calculate cycle length
        break;
      }
      w[i % n] = x;
    }
    if (i - v[x] > n) { // If we went too far without reaching target
      cout << "-1\n";
      return;
    }
  }
  if (x == to) { // We haven't cycled yet, return directly
    cout << v[to] << '\n';
  } else { // Use cycle to fast-forward to desired position
    cout << v[(to - s - 1) % (e - s) + s + 1] + d * ((to - s - 1) / (e - s))
         << '\n';
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/