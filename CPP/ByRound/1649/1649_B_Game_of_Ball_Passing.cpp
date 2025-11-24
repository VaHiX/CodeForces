// Problem: CF 1649 B - Game of Ball Passing
// https://codeforces.com/contest/1649/problem/B

/*
B. Game of Ball Passing

Algorithm: 
- For each test case, we compute the minimum number of balls required such that
  each player's pass count can be satisfied by distributing the balls among them.
- Key insight:
  - Let `s` be the total number of passes across all players.
  - Let `mx` be the maximum number of passes by any one player.
  - If `2 * mx <= s`, then we can distribute the passes using only 1 ball (each pass is a transfer among players).
  - Otherwise, we need at least `2 * mx - s` additional balls to satisfy the maximum player's pass count.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll s(0), mx(0);         // s = total passes, mx = max passes by any player
    for (ll p = 0; p < n; p++) {
      ll a;
      scanf("%lld", &a);
      s += a;               // accumulate total passes
      mx = (mx > a ? mx : a); // track maximum passes
    }
    if (!s) {               // if no passes, no balls needed
      puts("0");
    } else if (2 * mx <= s) { // if max passes can be covered by 1 ball
      puts("1");
    } else {
      printf("%lld\n", 2 * mx - s); // compute minimum extra balls needed
    }
  }
}


// https://github.com/VaHiX/codeForces/