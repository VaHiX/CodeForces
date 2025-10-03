// Problem: CF 2123 B - Tournament
// https://codeforces.com/contest/2123/problem/B

/*
B. Tournament

Purpose:
This code determines whether a specific player j can survive to be among the last k players in a tournament where players compete in pairs and the weaker player is eliminated. The tournament continues until only k players remain.

Algorithm:
- For each test case, we scan through all player strengths.
- We track the maximum strength (mx) of all players and store the strength of player j (s).
- If k == 1, player j must have the highest strength to be the sole survivor.
- Otherwise, if player j's strength is less than the maximum strength, it is impossible for j to survive to the end.

Time Complexity: O(n) per test case
Space Complexity: O(1)

Techniques:
- Single pass scan of array
- Greedy logic: player j can only win if their strength is at least max strength (when k=1)
- Simulated tournament behavior without actual simulation

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, j, k;
    scanf("%ld %ld %ld", &n, &j, &k);
    long s(-1), mx(-1);  // s: strength of player j, mx: maximum strength
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p + 1 == j) {  // If current player is player j
        s = x;
      }
      mx = (mx > x ? mx : x);  // Update maximum strength
    }
    puts((k == 1 && s < mx) ? "NO" : "YES");  // If k==1 and j's strength is less than max, impossible
  }
}


// https://github.com/VaHiX/codeForces/