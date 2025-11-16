// Problem: CF 1876 B - Effects of Anti Pimples
// https://codeforces.com/contest/1876/problem/B

/*
Code Purpose:
This code solves the problem of computing the sum of scores over all possible ways to select black indices in an array. 
Each selection of black indices causes certain elements to become green (multiples of black indices), and the score is the maximum value among all black and green elements.
The solution uses a technique that precomputes maximum values for each index considering its multiples, then uses inclusion-exclusion principle via powers of 2 to calculate contribution of each element.

Algorithms/Techniques:
- Preprocessing to find maximum values in subarrays based on divisor relationships
- Sorting in descending order
- Using powers of 2 to represent inclusion of elements in subsets
- Modular arithmetic to handle large numbers

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <iostream>

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll int, ll int>
#define ff first
#define ss second
#define pb push_back
#pragma GCC optimize("O2")
using namespace std;
#ifdef POTATO
#include "debug.h"

#define debug(...)                                                             \
  cerr << "[" << #__VA_ARGS__ << "] = [";                                      \
  _print(__VA_ARGS__)
#else
#define debug(...)
#endif
inline void yes() {
  cout << "YES" << endl;
  return;
}
inline void no() {
  cout << "NO" << endl;
  return;
}
template <class T> inline void out(T temp) {
  cout << temp << endl;
  return;
}
#define int long long
const int MOD = 998244353;
const int mxN = 1e5 + 10;
int n;
int a[mxN];
int pow2[mxN];
void init() {
  pow2[0] = 1;
  for (int i = 1; i < mxN; i++)
    pow2[i] = (pow2[i - 1] * 2) % MOD;
}
void solve(int &case_no) {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  // Preprocessing: for each index i, update a[i] to be maximum of itself and its multiples
  for (int i = n; i >= 1; i--) {
    for (int j = i * 2; j <= n; j += i) {
      a[i] = max(a[i], a[j]);
    }
  }
  // Sort the updated array in descending order
  sort(a + 1, a + n + 1, greater<int>());
  int ans = 0;
  // For each element, compute its contribution multiplied by number of subsets that include it
  for (int i = 1; i <= n; i++) {
    ans = (ans + (a[i] * pow2[n - i])) % MOD;
  }
  out(ans);
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  srand(time(NULL));
#ifdef POTATO
  auto start = chrono::high_resolution_clock::now();
#endif
  init();
  int t = 1;
  for (int i = 1; i <= t; i++)
    solve(i);
#ifdef POTATO
  auto end = chrono::high_resolution_clock::now();
  cerr << "Execution time: "
       << chrono::duration_cast<chrono::milliseconds>(end - start).count()
       << " ms" << endl;
#endif
}


// https://github.com/VaHiX/CodeForces/