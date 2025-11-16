// Problem: CF 2164 A - Sequence Game
// https://codeforces.com/contest/2164/problem/A

/*
Algorithm: Sequence Game
Purpose: Determine if a final number x can be obtained by repeatedly merging adjacent elements in an array,
         where the merged value must be within the range of the two adjacent elements.

Approach:
- The key insight is that during the merging process, each intermediate value must lie between the minimum 
  and maximum values of the original array. This is because:
    1. We can only merge adjacent elements.
    2. The new value must be within the range of the two elements being merged.
    3. Thus, the final value must also be within the range of all elements.
- So, we simply check if x lies within the range [min(A), max(A)].

Time Complexity: O(n) per test case - We iterate through the array once to find min and max.
Space Complexity: O(1) - Only using a few variables, not dependent on input size.

Techniques:
- Single pass to find minimum and maximum values.
- Simple range check.
*/

#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define ll long long
#define ull unsigned long long
#define rep(a, b) for (ll a = 0; a < b; a++)
#define rep2(a, c, b) for (ull a = c; a < b; a++)
#define myout(a)                                                               \
  rep(i, a.size()) cout << a[i] << " ";                                        \
  cout << "\n";
#define myout2(a)                                                              \
  rep(i, a.size()) {                                                           \
    rep(j, a[i].size()) cout << a[i][j] << " ";                                \
    cout << "\n";                                                              \
  }
#define mmax(a, b) (a > b ? a : b)
#define mmin(a, b) (a > b ? b : a)
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const long long INF = (1ULL << 60);
#define maxN 200005
#define ABS(x) (x > 0 ? x : -x)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll TT;
  cin >> TT;
  rep(TC, TT) {
    ll n;
    cin >> n;
    vector<ll> A(n);
    rep(i, n) cin >> A[i];
    ll x;
    cin >> x;
    ll m = INF, M = -INF;
    rep(i, n) {
      m = mmin(m, A[i]);   // Find minimum element
      M = mmax(M, A[i]);   // Find maximum element
    }
    string ans = "NO";
    if (m <= x && x <= M)    // Check if x is within [min, max]
      ans = "YES";
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/