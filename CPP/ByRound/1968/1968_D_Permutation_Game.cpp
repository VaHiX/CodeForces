// Problem: CF 1968 D - Permutation Game
// https://codeforces.com/contest/1968/problem/D

/*
D. Permutation Game

Algorithms/Techniques:
- Simulation with cycle detection in permutation
- Prefix sums for efficient score calculation
- Optimization using cycle length to avoid unnecessary iterations when k is large

Time Complexity: O(n) per test case, where n is the length of the permutation.
Space Complexity: O(n) for storing the permutation and array.

The game involves two players moving through a permutation with a fixed number of turns,
and each turn contributes to the score based on the value of the current position.
We simulate both players' moves, taking advantage of cycles in the permutation to
avoid redundant computation when k is large.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k, pb, ps;
    scanf("%lld %lld %lld %lld", &n, &k, &pb, &ps);
    std::vector<ll> m(n + 1); // permutation array
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &m[p]);
    }
    std::vector<ll> a(n + 1); // score array
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &a[p]);
    }
    
    // Bodya's simulation
    ll idxb(pb), csb(0), kb(k), scoreb(0), mxb(0);
    do {
      scoreb = std::max(scoreb, csb + kb * a[idxb]); // update max score with potential future bonus
      csb += a[idxb]; // accumulate current score
      --kb;
      idxb = m[idxb]; // move to next position in permutation
    } while (kb && idxb != pb); // stop if no more moves or back to start

    // Sasha's simulation
    ll idxs(ps), css(0), ks(k), scores(0), mxs(0);
    do {
      scores = std::max(scores, css + ks * a[idxs]); // update max score with potential future bonus
      css += a[idxs]; // accumulate current score
      --ks;
      idxs = m[idxs]; // move to next position in permutation
    } while (ks && idxs != ps); // stop if no more moves or back to start

    if (scoreb == scores) {
      puts("Draw");
    } else {
      puts(scoreb > scores ? "Bodya" : "Sasha");
    }
  }
}


// https://github.com/VaHiX/codeForces/