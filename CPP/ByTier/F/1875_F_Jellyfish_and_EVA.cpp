// Problem: CF 1875 F - Jellyfish and EVA
// https://codeforces.com/contest/1875/problem/F

/*
 * Problem: Jellyfish and EVA
 * 
 * Purpose: To find the maximum probability of successfully reaching city n from city 1,
 *          where both Jellyfish and Asuka choose roads optimally. Jellyfish chooses
 *          optimally, while Asuka chooses randomly. If both choose roads ending in the
 *          same city, EVA moves there; otherwise, it stays and both roads are destroyed.
 * 
 * Algorithm:
 * 1. Precompute dp[i][j] representing the probability of reaching the j-th largest
 *    value among i choices.
 * 2. For each node, calculate the probability of reaching the destination using
 *    dynamic programming and optimal choices.
 * 
 * Time Complexity: O(N^2) preprocessing + O(N * M) per test case, where N = 5000, M = 2*10^5
 * Space Complexity: O(N^2) for dp table + O(N + M) for graph storage
 * 
 * Techniques Used:
 * - Dynamic Programming
 * - Probability Calculation
 * - Greedy Choice (Jellyfish chooses optimally)
 * - Preprocessing
 */

#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
typedef long long ll;
#define fio                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ff first
#define ss second
const int MOD = 1e9 + 7;
const ll INF = 1e18;
ll add(ll a, ll b) {
  a = a % MOD;
  b = b % MOD;
  return (a + b) % MOD;
}
ll sub(ll a, ll b) {
  a = a % MOD;
  b = b % MOD;
  return (a - b + MOD) % MOD;
}
ll mul(ll a, ll b) {
  a = a % MOD;
  b = b % MOD;
  return ((a * b) % MOD + MOD) % MOD;
}
ll mod_pow(ll n, ll x) {
  ll res = 1;
  while (x > 0) {
    if (x % 2 == 1)
      res = (res * n) % MOD;
    n = (n * n) % MOD;
    x /= 2;
  }
  return res;
}
const int N = 5001;
double dp[N + 1][N + 2]; // dp[i][j] represents probability of having j-th largest value among i choices
void preprocess() {
  dp[1][1] = 1;
  dp[2][1] = 0.5;
  for (int i = 3; i <= N; i++) {
    dp[i][1] = 1.0 / i; // If choosing minimal value, we have 1/i chance
    for (int j = 2; j <= i; j++) {
      // Recurrence relation: 
      // Probability of getting j-th largest = probability of getting (j-2)th among (i-2) choices + probability of getting (j-1)th among (i-2) choices
      dp[i][j] = ((j - 2) * 1.0 / i) * dp[i - 2][j - 2] +
                 ((i - j) * 1.0 / i) * dp[i - 2][j - 1];
    }
  }
}
bool comp(double a, double b) { return a > b; } // Comparator for sorting probabilities in descending order
void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1); // Adjacency list for graph
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
  }
  vector<double> p(n + 1, 0); // p[i] stores probability of reaching city n from city i
  p[n] = 1; // Base case: probability of reaching n from n is 1
  for (int i = n - 1; i >= 1; i--) {
    int k = g[i].size(); // Number of edges from node i
    vector<double> temp(1, 0); // Temporary vector for sorted probabilities
    for (int x : g[i]) {
      temp.pb(p[x]); // Add probabilities of reaching destinations of edges from i
    }
    sort(temp.begin() + 1, temp.end(), comp); // Sort in descending order (greedy choice)
    for (int j = 1; j <= k; j++) {
      p[i] += temp[j] * dp[k][j]; // Accumulate probabilities using precomputed dp
    }
  }
  cout << fixed << setprecision(12) << p[1] << "\n"; // Output probability of reaching city n from city 1
}
int main() {
  fio;
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  preprocess(); // Precompute the dp table
  int tc = 1;
  cin >> tc;
  while (tc--) {
    solve(); // Process each test case
  }
}


// https://github.com/VaHiX/CodeForces/