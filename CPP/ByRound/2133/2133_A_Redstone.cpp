// Problem: CF 2133 A - Redstone?
// https://codeforces.com/contest/2133/problem/A

#include <cstdio>
#include <iostream>
using namespace std;
int vis[110]; // Visited array to count occurrences of each gear size
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 100; i++)
      vis[i] = 0; // Reset the visited array for each test case
    int ans = 0; // Counter for tracking mismatches in gear rotations
    while (n--) {
      int opt;
      scanf("%d", &opt);
      ans += vis[opt]; // If this gear size was already seen, increment mismatch counter
      vis[opt]++; // Mark that this gear size has been encountered
    }
    printf("%s\n", ans > 0 ? "YES" : "NO"); // If any mismatch occurred, it's possible to arrange gears
  }
}
/*
Flowerbox:
Purpose: This code determines whether gears can be arranged such that the rightmost gear spins at exactly 1 revolution per second.
Algorithm: It simulates the gear interaction by counting occurrences of gear sizes and checking for imbalances. If a gear size is repeated (indicating possible mismatch in rotation ratios), it marks an imbalance.
Time Complexity: O(n) per test case, where n is the number of gears.
Space Complexity: O(1) since the size of the vis array is fixed at 100.
*/

// https://github.com/VaHiX/codeForces/