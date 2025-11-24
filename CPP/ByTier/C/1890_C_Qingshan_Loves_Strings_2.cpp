// Problem: CF 1890 C - Qingshan Loves Strings 2
// https://codeforces.com/contest/1890/problem/C

/*
Purpose: This code solves the problem of making a binary string "good" by inserting "01" substrings.
A string is "good" if for every position i, the character at i is different from the character at position (length+1-i).
The approach uses a deque to process the string from both ends, inserting "01" when needed to balance the string.

Algorithms: Deque-based simulation with greedy insertion strategy.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing the string and the operations.
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define hello()                                                                \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define nl "\n"
#define yes cout << "YES" << nl
#define no cout << "NO" << nl
#define pb push_back
#define mod 1000000007
#define mem(a, x) memset(a, x, sizeof(a))
bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
  if (a.first != b.first) {
    if (a.first < b.first)
      return true;
    return false;
  } else {
    if (a.second < b.second)
      return true;
    return false;
  }
}
ll isqrt(ll x) {
  ll ans = 0;
  for (ll k = 1LL << 30; k != 0; k /= 2) {
    if ((ans + k) * (ans + k) <= x) {
      ans += k;
    }
  }
  return ans;
}
ll bin(ll n, ll pow) {
  ll result = 1;
  while (pow) {
    if (pow & 1) {
      result = (result * n);
    }
    n = (n * n);
    pow >>= 1;
  }
  return result;
}
const int N = 1e3 + 12;
void solve() {
  ll n;
  cin >> n;
  string s;
  cin >> s;
  int o = count(s.begin(), s.end(), '1'); // Count of 1s
  int z = n - o; // Count of 0s
  if (z != o) { // If counts are unequal, impossible to make good
    cout << -1 << nl;
    return;
  }
  deque<char> dq; // Deque to process string from both ends
  for (auto u : s)
    dq.pb(u);
  int l = 1, r = n; // l = left index, r = right index
  vector<int> ans; // Store positions where '01' is inserted
  while (dq.size()) { // While deque is not empty
    int x = dq.front(); // Front element
    int y = dq.back(); // Back element
    if (x != y) { // If front and back are different, remove them
      dq.pop_back();
      dq.pop_front();
      l++;
      r--;
    } else { // If same, insert '01' to balance
      if (x == '1') { // If both are '1', insert '01' at left
        ans.pb(l - 1);
        dq.push_front('1');
        dq.push_front('0');
        r += 2;
      } else { // If both are '0', insert '01' at right
        ans.pb(r);
        dq.push_back('0');
        dq.push_back('1');
        r += 2;
      }
    }
  }
  cout << ans.size() << nl; // Print number of operations
  for (auto u : ans) // Print positions
    cout << u << " ";
  cout << nl;
}
int main() {
  hello();
  cout.precision(10);
  cout.setf(ios::fixed);
  int tc;
  cin >> tc;
  while (tc--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/