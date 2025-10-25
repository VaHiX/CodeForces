// Problem: CF 2149 F - Nezuko in the Clearing
// https://codeforces.com/contest/2149/problem/F

/*
F. Nezuko in the Clearing
Algorithm: Binary search on the answer with mathematical formula to compute required turns.
Time Complexity: O(t * log(d)) where t is number of test cases and d is destination.
Space Complexity: O(1) - only using a few variables.

Problem Summary:
Nezuko starts at position 0 with h health and wants to reach position d.
There are two actions:
1. Move forward one step, which costs health equal to the number of consecutive moves (j-th move costs j).
2. Rest, which increases health by 1 (costs 1 turn).

Goal: find minimum total number of turns to reach d.

Approach:
We perform binary search on the number of resting turns (l). For a given number of rests,
we calculate how much health is required to make all the moves without dying.
Then we check if it's possible to complete with this many rests or more.

Key Formula:
For m consecutive rests and d moves:
- Total moves = d + m
- Health needed = sum of 1..d, but with some adjustment due to resting pattern.
- We calculate z as maximum health needed for given number of rests (m).
*/

#include <iostream>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long t, h, d, l, r, m, x, y, z;
  cin >> t;
  while (t--) {
    cin >> h >> d;
    l = 0;                   // Lower bound of rests
    r = d + 1;               // Upper bound of rests
    while (l != r) {
      m = (l + r) / 2;       // Midpoint - number of rests to try
      x = d / (m + 1);       // Base number of moves per group
      y = d % (m + 1);       // Extra moves in last incomplete group
      // Compute total health required for m rests and d moves
      z = (m + 1 - y) * x * (x + 1) / 2 + y * (x + 1) * (x + 2) / 2;
      if (h + m > z)
        r = m;               // Too many rests, reduce
      else
        l = m + 1;           // Not enough rests, increase
    }
    cout << d + l << '\n';   // Total turns = moves + rests
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/