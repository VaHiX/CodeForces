// Problem: CF 2133 A - Redstone?
// https://codeforces.com/contest/2133/problem/A

/*
Problem: Determine if gears can be arranged so that the rightmost gear spins at 1 revolution per second.

Algorithms/Techniques:
- Simulation with gear ratio calculations
- For a sequence of gears, speed is calculated as (prev_teeth / curr_teeth) * prev_speed
- The key idea is to check whether any permutation leads to final speed = 1

Time Complexity: O(n^2) per test case
Space Complexity: O(1) additional space (vis array size fixed at 100)

This problem reduces to checking if the product of all ratios in some order results in 1.
*/
#include <cstdio>
#include <iostream>
using namespace std;
int vis[110]; // Frequency counter for teeth values
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 100; i++)
      vis[i] = 0; // Reset frequency array
    int ans = 0; // Count of conflicts (repeated teeth values)
    while (n--) {
      int opt;
      scanf("%d", &opt);
      ans += vis[opt]; // If already seen, increment conflict count
      vis[opt]++; // Mark this tooth value as seen
    }
    printf("%s\n", ans > 0 ? "YES" : "NO"); // If conflicts exist, arrangement possible
  }
}


// https://github.com/VaHiX/CodeForces/