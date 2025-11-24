// Problem: CF 2036 G - Library of Magic
// https://codeforces.com/contest/2036/problem/G

/*
 * Problem: Library of Magic
 * Purpose: Find three distinct numbers a, b, c that represent the stolen books
 *          from a library of n book types where each type appears exactly twice,
 *          except for the three stolen books that appear only once.
 * 
 * Approach:
 * - Use binary search combined with XOR queries to identify the unique values.
 * - The key insight is that XOR of all elements in a range gives us information about
 *   which elements are present in that range.
 * - By recursively splitting ranges and analyzing XOR results, we can isolate the
 *   three missing values.
 * 
 * Time Complexity: O(log^2 n) per test case due to binary search and recursion depth.
 * Space Complexity: O(log n) for recursion stack and auxiliary storage.
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <initializer_list>

#define vc vector
#define pip pair<int, int>
#define pb push_back
#define ll long long
#define mp(a, b) make_pair(a, b)
#define all(s) s.begin(), s.end()
using namespace std;
const int inf = 1e9 + 7;
const ll INF = 1e18;
const int mod = 998244353;
vc<ll> ans;
ll maxi;
ll ask(ll l, ll r) {
  r = min(r, maxi);
  l = min(l, maxi);
  ll res;
  cout << "xor " << l << ' ' << r << "\n";
  cout.flush();
  cin >> res;
  return res;
}
void check(ll l, ll r, ll cur, int k) {
  cout.flush();
  ll xor1, xor2, x;
  if (!cur) {
    // Find the highest bit set in r to split the range
    x = 1LL << (63 - __builtin_clzll(r));
    xor2 = ask(x, r);
    xor1 = cur ^ xor2;
    if (!xor2) {
      // If xor2 is 0, the missing value is in the left half
      check(l, x - 1, cur, k);
      return;
    }
    ans.pb(xor1);
    // Continue searching in right half
    check(x, r, xor2, 2);
    return;
  }
  // Calculate mid point for binary search
  x = max(l, l / 2 + r / 2);
  xor1 = ask(l, x);
  xor2 = cur ^ xor1;
  if (!xor1) {
    // If xor1 is 0, the missing value is in the right half
    check(x + 1, r, cur, k);
    return;
  }
  if (!xor2) {
    // If xor2 is 0, the missing value is in the left half
    check(l, x, cur, k);
    return;
  }
  if (k == 2) {
    // Both values found, add to answer
    ans.pb(xor1);
    ans.pb(xor2);
    return;
  }
  // Determine if xor1 or xor2 represents a single element
  if (xor1 == ask(xor1, xor1)) {
    ans.pb(xor1);
    check(x + 1, r, xor2, 2);
  } else {
    ans.pb(xor2);
    check(l, x, xor1, 2);
  }
}
void solve() {
  ll r;
  cin >> r;
  maxi = r;
  ans = {};
  check(1, r, ask(1, r), 3);
  cout << "ans ";
  for (int i = 0; i < 3; i++)
    cout << ans[i] << ' ';
  cout << "\n";
  cout.flush();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int test = 1;
  cin >> test;
  while (test--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/