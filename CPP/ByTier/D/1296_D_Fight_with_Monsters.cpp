// Problem: CF 1296 D - Fight with Monsters
// https://codeforces.com/contest/1296/problem/D

/*
D. Fight with Monsters

Purpose:
This code solves the problem of maximizing the number of points you can gain in a monster fighting game, 
where you and your opponent take turns attacking monsters. You gain a point if you kill a monster on your turn, 
and your opponent gains nothing whether they kill it or not. A secret technique allows you to skip your opponent's turn,
which can be used at most k times total across all monsters.

Approach:
1. For each monster, compute how many turns of attacks (you + opponent) are needed to kill the monster.
2. Compute how many times you need to use the secret technique on a monster to gain an extra point.
3. Sort these values to greedily select which monsters to apply the technique on.

Time Complexity: O(n * log(n)) due to sorting.
Space Complexity: O(n) for storing the vector of turns per monster.

Algorithms/Techniques:
- Greedy algorithm
- Sorting
- Mathematical computation of turns needed

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, a, b, k;
  scanf("%lld %lld %lld %lld", &n, &a, &b, &k);
  std::vector<ll> f(n);
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    const ll s = a + b; // Total damage per full round (you + opponent)
    x = (x % s == 0) ? s : (x % s); // Normalize x to within one round
    x = (x > a) ? (x - a) : 0; // If x <= a, then you kill it on your turn anyway, so no need for technique
    f[p] = (x + a - 1) / a; // Number of times you attack to finish off the monster after opponent's hits
  }
  sort(f.begin(), f.end()); // Sort by required attacks to know how to optimally apply secret technique
  ll cnt(0);
  for (ll p = 0; k && p < n; p++) {
    cnt += (k >= f[p]); // Use the secret technique if possible, gain point
    k -= f[p]; // Deduct the number of required turns from the available k
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/