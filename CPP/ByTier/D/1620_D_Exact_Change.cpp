// Problem: CF 1620 D - Exact Change
// https://codeforces.com/contest/1620/problem/D

#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;
map<int, int> m;
int _, n, i, p, vis[3], a[200001];
int main() {
  scanf("%d", &_);
  while (_--) {
    scanf("%d", &n);
    m.clear();
    for (i = 1; i <= n; i++)
      scanf("%d", &a[i]),
          m[a[i]] = 1;      // Read input and store unique costs in map
    sort(a + 1, a + n + 1); // Sort the costs in ascending order
    p = a[n] / 3; // Initialize p with the number of 3-burle coins needed for
                  // the most expensive flavor
    vis[0] = 1;   // Mark that we can make amounts divisible by 3
    vis[1] = vis[2] = 0; // Reset flags for remainders 1 and 2
    for (i = 1; i <= n; i++)
      if (!vis[a[i] % 3]) // If we haven't seen a flavor with this remainder yet
        vis[a[i] % 3] = 1, p++; // Increment p and mark this remainder as seen
    if (vis[1] && vis[2] &&
        a[n] % 3 == 0) // If both remainders 1 and 2 are seen and max cost is
                       // divisible by 3
      p--; // One 3-burle coin can be saved because we already have combinations
           // for 1 and 2
    if (vis[1] && vis[2] && a[n] > 2 && a[n] % 3 == 1 && !m[a[n] / 3 * 3] &&
        a[1] > 1)
      p--; // Another adjustment for edge case when optimal solution can be
           // improved
    printf("%d\n", p); // Output the minimum number of coins required
  }
}

// ### Complexity Analysis:
// - **Time Complexity:** O(n log n) per test case due to sorting, where n is
// the number of flavors.
// - **Space Complexity:** O(n) for storing the input and auxiliary arrays.

// ### Algorithm/Techniques:
// This code aims to find the minimum number of coins (1, 2, and 3 burles)
// needed such that any given cost can be made in exact change. It uses a greedy
// approach with adjustments based on the remainders of the costs when divided
// by 3, leveraging the fact that we can always use combinations of 1's and 2's
// to cover all combinations not divisible by 3. The logic accounts for specific
// cases where optimal combinations may reduce the overall number of coins
// required.

// https://github.com/VaHiX/CodeForces/