// Problem: CF 1970 B2 - Exact Neighbours (Medium)
// https://codeforces.com/contest/1970/problem/B2

/*
Purpose: This code solves the problem of placing n wizards' houses on an n×n grid such that:
1. Each wizard's house is at a unique column (no two wizards share the same x-coordinate).
2. Each wizard visits another wizard's house at exactly distance a[i] (Manhattan distance).
The algorithm constructs positions row by row, ensuring that the distance constraint is satisfied.

Algorithms/Techniques: Greedy placement with Manhattan distance calculation and column uniqueness enforcement.

Time Complexity: O(n) - Single pass through the array to compute positions and answers.
Space Complexity: O(n) - Storing positions and answer vectors of size n.

*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define mod 1000000007
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie();
  cout.tie();
  int n;
  cin >> n;
  vector<int> v(n + 1); // Array to store the distances a[i] for each wizard
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
  }
  vector<int> x(n + 1), y(n + 1), ans(n + 1); // x, y coordinates for houses and answer mapping
  x[1] = 1; // Fix the first wizard's house at (1,1)
  y[1] = 1;
  ans[1] = 1; // The first wizard visits their own house
  for (int i = 2; i <= n; i++) {
    ans[i] = max(1, i - v[i]); // Determine which wizard's house the i-th wizard should visit
    x[i] = i; // Set x-coordinate to i to ensure column uniqueness
    if (i - v[i] < 1) {
      // If the required wizard index is less than 1, compute y based on distance and column offset
      y[i] = y[1] + v[i] - (i - 1);
    } else {
      // Otherwise, use the known y-coordinate of the target wizard
      if (v[i]) {
        y[i] = y[i - v[i]];
      } else {
        // If the distance is 0, set y to 1 (as the wizard visits themselves)
        y[i] = 1;
      }
    }
  }
  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    cout << x[i] << " " << y[i] << "\n"; // Output the positions of all houses
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " "; // Output for each wizard, which wizard's house they visit
  }
  cout << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/