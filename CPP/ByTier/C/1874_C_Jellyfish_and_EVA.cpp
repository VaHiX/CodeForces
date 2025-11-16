// Problem: CF 1874 C - Jellyfish and EVA
// https://codeforces.com/contest/1874/problem/C

/*
Algorithm: Dynamic Programming with Probability Calculation
- Time Complexity: O(n^2 + m) where n is the number of nodes and m is number of
edges
- Space Complexity: O(n^2 + m) for storing DP table, adjacency lists, and
temporary arrays

The problem models a probabilistic game where two players (Jellyfish and Asuka)
choose roads from city u, and the EVA moves to a city only if both choose the
same destination. Otherwise, both roads are destroyed.

The solution works by computing the probability of reaching the final city n
from each city j, using dynamic programming:
1. Initialize f[n] = 1 (success probability from final city)
2. For each city j from n-1 down to 1:
   - Get all possible destinations from j
   - Compute the probability of reaching destination v using the precomputed DP
table
   - Sort these probabilities to find the optimal strategy for Jellyfish
   - Sum up weighted probabilities using DP values
3. Return f[1] which is the maximum probability of success from starting city

This approach treats the optimal choice of Jellyfish as choosing roads that
maximize the probability of reaching n, considering Asuka's random choice.
*/
#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>

#define ll long long

using namespace std;
namespace YYZ {
const ll N = 5010;
const ll W = 5000;
ll n, m;
ll T;
double dp[N][N];
vector<ll> vec[N];
double to[N];
ll cnt = 0;
double f[N];
void clr() {
  for (ll i = 1; i <= n; i++)
    vec[i].clear();
}
void solve() {
  cin >> n >> m;
  clr();
  ll u, v;
  for (ll i = 1; i <= m; i++) {
    cin >> u >> v;
    vec[u].push_back(v);
  }
  f[n] = 1.0;
  for (ll j = n - 1; j >= 1; j--) {
    cnt = 0;
    for (auto v : vec[j]) {
      to[++cnt] = f[v];
    }
    f[j] = 0.0;
    sort(to + 1, to + cnt + 1, greater<double>());
    for (ll k = 1; k <= cnt; k++) {
      f[j] += to[k] * dp[cnt][k];
    }
  }
  printf("%.12lf\n", f[1]);
}
void main() {
  for (ll i = 1; i <= W; i++) {
    dp[i][1] = 1.0 / (double)i;
    for (ll j = 2; j <= i; j++)
      dp[i][j] = (dp[i - 2][j - 1] * (double)(i - j) +
                  dp[i - 2][j - 2] * (double)(j - 2.0)) /
                 (double)i;
  }
  cin >> T;
  while (T--) {
    solve();
  }
}
} // namespace YYZ
int main() {
  ll T = 1;
  while (T--)
    YYZ::main();
  return 0;
}

// https://github.com/VaHiX/CodeForces/