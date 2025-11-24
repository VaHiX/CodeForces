// Problem: CF 2133 D - Chicken Jockey
// https://codeforces.com/contest/2133/problem/D

/*
D. Chicken Jockey
Algorithms/Techniques: Dynamic Programming, Simulation with Stack Behavior

Time Complexity: O(n) per test case
Space Complexity: O(n) for the arrays d and ar

This problem simulates a chicken jockey stack where mobs can die and cause cascading falls.
Each mob has health, and when it dies, mobs above it fall down with damage based on the number of mobs below them.
The goal is to find the minimum number of attacks to eliminate all mobs.

We use dynamic programming to compute for each position i, the minimum number of attacks needed to eliminate
the first i mobs, considering two possible strategies:
1. Attack the current mob directly and let it fall.
2. Attack a previous mob such that the current mob takes fall damage from that attack.

The recurrence relation computes optimal cost by choosing between two cases:
- Direct attack: d[i - 1] + (ar[i] - 1)
- Indirect attack: d[i - 2] + (ar[i - 1] + max(0, ar[i] - i + 1))

*/

#include <iostream>
#include <algorithm>

#define int long long
#define endl '\n'
using namespace std;
int ar[200005], d[200005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> ar[i];
    d[1] = ar[1]; // Base case: need ar[1] attacks to kill first mob
    for (int i = 2; i <= n; i++) {
      // Two transition options:
      // 1. Attack current mob directly and add fall damage from previous mob (if it died)
      // 2. Attack mob before previous, so we can save some damage on current
      d[i] = min(d[i - 1] + ar[i] - 1,
                 d[i - 2] + ar[i - 1] + max(0ll, ar[i] - i + 1));
    }
    cout << d[n] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/