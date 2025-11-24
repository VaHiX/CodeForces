// Problem: CF 1217 B - Zmei Gorynich
// https://codeforces.com/contest/1217/problem/B

/*
B. Zmei Gorynich
Algorithms: Greedy with binary search or direct simulation approach.
Time Complexity: O(n) per test case, where n is the number of blow types.
Space Complexity: O(1), only using a few variables.

Problem Description:
You are fighting with Zmei Gorynich — a ferocious monster from Slavic myths,
a huge dragon-like reptile with multiple heads!
Initially Zmei Gorynich has x heads. You can deal n types of blows.
If you deal a blow of the i-th type, you decrease the number of Gorynich's heads
by min(d_i, curX), where curX is the current number of heads.
But if after this blow Zmei Gorynich has at least one head, he grows h_i new heads.
If curX = 0 then Gorynich is defeated.
You can deal each blow any number of times, in any order.
Calculate the minimum number of blows to defeat Zmei Gorynich!

Approach:
1. Find maximum reduction (d) and maximum net gain (d - h) over all moves.
2. If initial x <= max reduction (mb), we need at least one move to reduce it.
3. If max net gain (mf) is less than or equal to 0, then no progress is possible.
4. For remaining heads after applying best single move, compute how many more
   moves are needed using the maximum net gain for optimization.
*/
#include <cstdio>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    ll mb(0), mf(0); // mb: max reduction, mf: max net gain
    for (ll p = 0; p < n; p++) {
      ll d, h;
      scanf("%lld %lld", &d, &h);
      mb = (mb > d) ? mb : d; // Track maximum reduction in one hit
      ll diff = d - h;
      mf = (mf > diff) ? mf : diff; // Track maximum net gain from one blow
    }
    if (x > mb && mf <= 0) { // If cannot make progress, defeat is impossible
      puts("-1");
    } else {
      ll cnt(1); // At least one blow is needed if we can reduce to 0
      x -= mb;   // Apply the best move once to get down as much as possible
      if (x > 0) {
        cnt += (x + mf - 1) / mf; // Add number of remaining blow rounds, using ceiling division
      }
      printf("%lld\n", cnt);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/