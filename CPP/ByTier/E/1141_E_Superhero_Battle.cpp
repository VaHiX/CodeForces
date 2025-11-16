// Problem: CF 1141 E - Superhero Battle
// https://codeforces.com/contest/1141/problem/E

/*
E. Superhero Battle
Algorithms/Techniques: Prefix sum, simulation, math
Time Complexity: O(n)
Space Complexity: O(n)

The problem models a superhero battle against a monster that fights in rounds.
Each round consists of n minutes, and each minute the monster's HP changes by 
a fixed amount (given in the sequence). The monster starts with H HP.

We simulate the first round to see if the monster dies during it. If not,
we calculate how many full cycles of the round are needed before the monster
reaches a point where it can die in the next round, using math and prefix sums.
*/

#include <cstdio>
typedef long long LL;
const int N = 2e5 + 50;
LL H, Ans, x, y; // x: total change of HP in one cycle; y: minimum prefix sum
int n, a[N];
int main() {
  scanf("%I64d%d", &H, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    x += a[i]; // accumulate the total change in one round
    if (y > x) // track minimum prefix sum to know lowest HP during a round
      y = x;
    if (H + x <= 0) { // if monster dies during this round
      printf("%d\n", i);
      return 0;
    }
  }
  if (x >= 0) { // if the round never decreases HP, the monster won't die
    puts("-1");
    return 0;
  }
  x = -x; // Convert to positive for calculation of cycles
  // Calculate number of full rounds needed before monster dies in next cycle
  Ans = 1ll * n * ((H + y) / x + ((H + y) % x > 0));
  H = H - 1ll * ((H + y) / x + ((H + y) % x > 0)) * x; // Adjust HP after full rounds
  for (int i = 1; i <= n; i++) {
    H += a[i]; // simulate one more round to find exact minute of death
    if (H <= 0) {
      printf("%I64d\n", Ans + i);
      return 0;
    }
  }
}


// https://github.com/VaHiX/codeForces/