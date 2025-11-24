// Problem: CF 1946 D - Birthday Gift
// https://codeforces.com/contest/1946/problem/D

/*
Purpose: 
  Find the maximum number of non-overlapping subarrays (segments) such that 
  the bitwise OR of XOR values of each segment does not exceed x.

Algorithms/Techniques:
  - Bit manipulation and greedy approach
  - For each bit position from high to low, try to determine if we can form 
    a valid partitioning of the array such that all segment XORs are 
    constrained to a certain subset of bits.
  - For each candidate bit mask, check if we can partition array greedily 
    to get a valid result.

Time Complexity: O(31 * n) = O(n), where n is size of array
Space Complexity: O(1) - only using a few variables and no extra space
*/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define ull unsigned long long
#define db double
#define pii pair<int, int>
#define pli pair<ll, int>
#define pil pair<int, ll>
#define pll pair<ll, ll>
#define ti3 tuple<int, int, int>
#define int128 __int128_t
#define pii128 pair<int128, int128>
const int inf = 1 << 30;
const ll linf = 1e18;
const db EPS = 1e-10;
const db pi = acos(-1);
template <class T> bool chmin(T &x, T y) {
  if (x > y) {
    x = y;
    return true;
  } else
    return false;
}
template <class T> bool chmax(T &x, T y) {
  if (x < y) {
    x = y;
    return true;
  } else
    return false;
}
#define CAT(A, B) A##B
#define SELECT(NAME, NUM) CAT(NAME, NUM)
#define GET_COUNT(_1, _2, _3, _4, _5, _6, COUNT, ...) COUNT
#define VA_SIZE(...) GET_COUNT(__VA_ARGS__, 6, 5, 4, 3, 2, 1)
#define VA_SELECT(NAME, ...) SELECT(NAME, VA_SIZE(__VA_ARGS__))(__VA_ARGS__)
#define rep(...) VA_SELECT(rep, __VA_ARGS__)
#define rep2(i, n) for (int i = 0; i < int(n); i++)
#define rep3(i, a, b) for (int i = a; i < int(b); i++)
#define rep4(i, a, b, c) for (int i = a; i < int(b); i += c)
#define repll(...) VA_SELECT(repll, __VA_ARGS__)
#define repll2(i, n) for (ll i = 0; i < (ll)(n); i++)
#define repll3(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define repll4(i, a, b, c) for (ll i = a; i < (ll)(b); i += c)
#define rrep(...) VA_SELECT(rrep, __VA_ARGS__)
#define rrep2(i, n) for (int i = n - 1; i >= 0; i--)
#define rrep3(i, a, b) for (int i = b - 1; i >= a; i--)
#define rrep4(i, a, b, c) for (int i = b - 1; i >= a; i -= c)
#define rrepll(...) VA_SELECT(rrepll, __VA_ARGS__)
#define rrepll2(i, n) for (ll i = (ll)(n) - 1; i >= 0ll; i--)
#define rrepll3(i, a, b) for (ll i = b - 1; i >= (ll)(a); i--)
#define rrepll4(i, a, b, c) for (ll i = b - 1; i >= (ll)(a); i -= c)
#define fore(e, v) for (auto &&e : v)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  rep(i, n) { cin >> a[i]; }
  int k = -1;
  rrep(i, 31) {  // Iterate from highest bit to lowest
    int y = ((1ll << 31) - (1ll << (i + 1))) & x;  // Create a mask for higher bits
    if (x >> i & 1) {  // If current bit of x is set
      y |= (1 << i) - 1;  // Set all lower bits
    } else {
      y = x;  // Otherwise use x as is
    }
    int val = 0, ans = 0, flag = 0;
    rep(i, n) {
      val ^= a[i];  // Accumulate XOR from left
      if ((val & y) == val) {  // If the XOR value is a submask of y
        val = 0;  // Reset XOR
        ans++;  // Increment answer count
        flag = true;
      } else {
        flag = false;
      }
    }
    if (flag)
      chmax(k, ans);  // Update maximum k if valid solution found
  }
  cout << k << '\n';
}
int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/