// Problem: CF 2165 B - Marble Council
// https://codeforces.com/contest/2165/problem/B

/*
Purpose:
This program computes the number of distinct multisets that can be generated from a given multiset,
following specific rules involving partitioning and choosing modes from each partition.

Approach:
- For each test case:
  1. Count the frequency of each element in the input multiset.
  2. Identify all unique frequencies (excluding zero).
  3. Use dynamic programming to count how many ways we can form subsets based on these frequencies.
  4. Calculate total number of possible outcomes, subtracting invalid cases.
  
Complexity:
Time Complexity: O(n^2) per test case, due to nested loops in DP computation.
Space Complexity: O(n) for storing frequency counts and DP array.
*/

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#define ll long long
#define siktir return
using namespace std;
mt19937 rng(time(NULL));
const ll N = 2e5 + 10, M = 998244353;
ll n, m, q, ans, a[N];
int main() {
  ios_base::sync_with_stdio(false);
  ll t;
  cin >> t;
  while (t--) {
    cin >> n;
    ll mx = 0, zar = 1, sum = 0;
    vector<ll> cnt(n + 10, 0), dp(n + 10, 0);
    for (ll i = 0; i < n; i++) {
      cin >> a[i];
      cnt[a[i]]++;
      mx = max(mx, cnt[a[i]]);
    }
    vector<ll> c;
    for (ll i = 1; i <= n; i++) {
      if (cnt[i] != 0) {
        c.push_back(cnt[i]);
        zar *= (cnt[i] + 1);
        zar %= M;
      }
    }
    dp[0] = 1;
    for (ll i = 0; i < c.size(); i++) {
      for (ll j = n; j >= c[i]; j--) {
        dp[j] += c[i] * dp[j - c[i]] % M;
        dp[j] %= M;
      }
    }
    for (ll i = 0; i < mx; i++) {
      sum += dp[i];
      sum %= M;
    }
    cout << (zar - sum + M) % M << endl;
  }
}


// https://github.com/VaHiX/CodeForces/