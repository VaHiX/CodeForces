// Problem: CF 1854 B - Earn or Unlock
// https://codeforces.com/contest/1854/problem/B

/*
Algorithm: Dynamic Programming with Bitset Optimization
Techniques: Bit manipulation, prefix sum, greedy thinking

Time Complexity: O(n^2 / 32) due to bitset operations and nested loops
Space Complexity: O(n) for the bitset and array storage

The problem involves maximizing victory points by choosing which unlocked cards to use,
and unlocking subsequent cards based on their values. We process cards from left to right 
and track reachable positions using a bitset.
*/

#include <algorithm>
#include <bitset>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define all(v) v.begin(), v.end()
#define compress(v) v.erase(unique(all(v)), v.end())
#define lbx(v, x) lower_bound(all(v), x) - v.begin()
#define ubx(v, x) upper_bound(all(v), x) - v.begin()
#define maxx(a, b) a = max(a, b)
#define minn(a, b) a = min(a, b)
#define for0(i, n) for (int i = 0; i < n; i++)
#define for1(i, n) for (int i = 1; i <= n; i++)
#define forr(i, l, r) for (int i = l; i <= r; i++)
#define sz(v) (int)v.size()
using namespace std;
typedef long long ll;
const int MAX = 200000;
int N;
ll A[200000];
bitset<MAX> DP, All;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  for0(i, N) cin >> A[i];
  DP.set(0, true);  // Initially the first card is unlocked
  for0(i, N) {
    DP |= (DP << A[i]);  // Unlock cards based on current card's value
    All |= DP;           // Track all possible unlocked positions
    DP.set(i, false);    // Mark current card as used (locked)
  }
  ll ans = 0;
  for0(i, 2 * N) {
    if (i)
      A[i] += A[i - 1];  // Compute prefix sums
    if (All[i])
      maxx(ans, A[i] - i);  // Maximize score with current reachable position
  }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/