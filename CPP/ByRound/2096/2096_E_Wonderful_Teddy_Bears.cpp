// Problem: CF 2096 E - Wonderful Teddy Bears
// https://codeforces.com/contest/2096/problem/E

/*
E. Wonderful Teddy Bears

Algorithm/Technique: Greedy + Simulation
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem asks for the minimum number of operations to make a sequence of black (B) and pink (P) teddy bears
beautiful — i.e., all B's come before all P's. Each operation allows reordering three consecutive elements so that
all B's are to the left of all P's in that group.

The approach uses a greedy idea:
- Count how many B's we've seen so far and track how many of those B’s are at odd positions (1-indexed).
- For each B encountered, compute how much "disorder" it contributes.
- At the end, the final answer combines this disorder with a correction term based on balancing B's between even/odd
  positions to ensure minimal operations.

Key Observations:
- We process the string from left to right.
- For every 'B', we consider its effect on the total cost:
    - It increases `a` (count of B's so far).
    - If its index is even, it contributes to `b`.
    - Add `i + 1 - a` to accumulate the cost from previous misplacements.
- A correction term uses absolute difference between half the total count of B's and count of B’s in even positions.

*/

#include <bits/std_abs.h>
#include <iostream>
#include <string>

using namespace std;
using i64 = long long;

int T;
int n;
i64 ans, a, b;
string s;

void solve() {
  a = b = ans = 0; // reset counters
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'B') { // when we see a black bear
      a++; // increment count of black bears seen so far
      b += !((i + 1) & 1); // increment if this black bear is at an even index (1-based)
      ans += i + 1 - a; // accumulate cost due to disorder introduced by this B
    }
  }
  cout << (ans + abs(a / 2 - b)) / 2 << '\n'; // compute result using derived formula
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/