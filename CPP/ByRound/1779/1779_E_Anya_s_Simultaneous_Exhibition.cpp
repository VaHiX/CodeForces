// Problem: CF 1779 E - Anya's Simultaneous Exhibition
// https://codeforces.com/contest/1779/problem/E

/*
Algorithm: Tournament Candidate Master Detection using Simultaneous Exhibitions
Approach:
1. For each player, conduct a simul where the player plays against all other players (n-1 games).
2. Record the number of wins for each player.
3. Sort players by their win counts in descending order.
4. Use a greedy approach to determine which players can be candidate masters:
   - Start with the player with the most wins.
   - For each subsequent player, check if including them in the set of candidate masters is valid.
   - If adding the current player would violate transitivity constraints, stop.
5. Output the binary string indicating candidate masters.

Time Complexity: O(n^2) due to sorting and iterative checking.
Space Complexity: O(n) for storing data structures.

Techniques:
- Binary search simulation (via sorting and greedy)
- Transitivity constraint checking
- Interactive problem solving with queries and responses
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 260;
int n, d[N], p[N], x;
char ans[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    printf("? %d ", i);
    for (int j = 1; j <= n; j++)
      putchar(i ^ j ? '1' : '0');  // Player i plays against all others (excluding self)
    puts(""), fflush(stdout);
    scanf("%d", &d[i]), p[i] = i, ans[i] = '0';  // Record wins, initialize candidate master flags
  }
  sort(p + 1, p + 1 + n, [](int x, int y) { return d[x] > d[y]; });  // Sort players by win count (descending)
  for (int i = 1, s = 0; i <= n; i++) {
    ans[p[i]] = '1', s += d[p[i]];  // Include player in candidates and accumulate wins
    if (s == i * (i - 1) / 2 + i * (n - i))  // Check if transitivity constraints are satisfied
      break;  // Stop if constraint is violated
  }
  printf("! %s\n", ans + 1), fflush(stdout);  // Output result as binary string
  return 0;
}


// https://github.com/VaHiX/CodeForces/