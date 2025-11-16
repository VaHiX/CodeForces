// Problem: CF 879 B - Table Tennis
// https://codeforces.com/contest/879/problem/B

/*
Purpose: Determine the winner of a table tennis tournament where players compete in a line,
         and the first player to win k consecutive games becomes the champion.

Algorithms/Techniques: Simulation with optimization to avoid unnecessary iterations.
                       The key insight is that once the strongest player is in the front,
                       they will win all subsequent matches until k consecutive wins.

Time Complexity: O(n), where n is the number of players. We simulate at most n-1 matches in the worst case.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>

typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  // Limit k to n to avoid redundant iterations
  k = (k < n) ? k : n;
  ll w;
  scanf("%lld", &w);
  ll count(0);  // Count of consecutive wins for current leader
  for (long p = 1; p < n; p++) {  // Iterate through remaining players
    ll x;
    scanf("%lld", &x);
    if (x > w) {  // If new player is stronger
      // Swap player positions (new stronger player becomes current leader)
      ll u = x;
      x = w;
      w = u;
      count = 1;  // Reset consecutive wins to 1
    } else {
      ++count;  // Increment consecutive wins for current leader
      if (count >= k) {  // If current leader has won k games in a row
        break;  // Exit early as this player is the winner
      }
    }
  }
  printf("%lld\n", w);  // Print the power of the winner
  return 0;
}


// https://github.com/VaHiX/CodeForces/