// Problem: CF 1498 D - Bananas in a Microwave
// https://codeforces.com/contest/1498/problem/D

/*
Algorithm: Dynamic Programming with BFS-like approach
Approach:
- Use a distance array dist where dist[i] represents the earliest time step to achieve exactly i bananas.
- Initially, dist[0] = 0 (0 bananas at step 0).
- For each operation in order:
  - Iterate through all current achievable banana counts (from m down to 0).
  - For each count, simulate applying the operation up to y times.
  - Update dist with the earliest time step when a new count is achieved.
- Output dist values for 1 to m.

Time Complexity: O(n * m * y_max), where n is number of operations, m is max bananas, y_max is max y value
Space Complexity: O(m), for the dist array storing the earliest time steps
*/

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
int dist[100005]; // dist[i] = earliest time step to get exactly i bananas
int main() {
  memset(dist, 255, sizeof(dist)); // Initialize all values to -1
  dist[0] = 0; // Base case: 0 bananas at time step 0
  int n, m;
  cin >> n >> m; // Read number of operations and max bananas to track
  for (int i = 1; i <= n; i++) {
    int t;
    long long x; // x'_i is read and converted to x_i by dividing by 100000
    int y;
    scanf("%d%lld%d", &t, &x, &y); // Read operation type, x value (scaled), and y limit
    for (int j = m; j >= 0; j--) { // Traverse from high to low to prevent reprocessing
      if (dist[j] == -1)
        continue; // Skip if this count is not reachable
      long long now = j; // Start with current number of bananas
      for (int k = 1; k <= y; k++) { // Try applying operation k times (1 to y)
        if (t == 1) {
          // Type 1: addition operation
          // x / 100000 is the integer part, !! (x % 100000) adds 1 if remainder exists
          now += x / 100000 + !!(x % 100000);
        } else {
          // Type 2: multiplication operation  
          // For multiplication, calculate the new value with ceiling
          now = now * x / 100000 + !!(now * x % 100000);
        }
        if (now > m || dist[now] != -1) // Stop if result exceeds m or already found
          break;
        dist[now] = i; // Record earliest time to reach this count
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    printf("%d ", dist[i]); // Print earliest time to achieve each banana count
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/