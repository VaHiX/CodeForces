// Problem: CF 2156 C - Maximum GCD on Whiteboard
// https://codeforces.com/contest/2156/problem/C

/*
Purpose: This code solves the problem of maximizing the GCD (Greatest Common Divisor) of integers on a whiteboard after performing at most k erase operations and any number of split operations.

Algorithm:
- For each possible GCD value (from 1 to n), we determine if it's achievable given the constraints.
- We use a frequency map to count occurrences of each number.
- We use prefix sums to quickly calculate how many numbers are >= a certain value.
- For a given GCD, we compute how many numbers we can potentially keep (by splitting or erasing) such that all remaining numbers are divisible by this GCD.
- If the required number of elements (n - k) can be satisfied, we update the maximum possible GCD.

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define vi vector<int>
#define vl vector<ll>
#define vc vector<char>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define vvc vector<vector<char>>
#define vvb vector<vector<bool>>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
const int M = 1e9 + 7;

// Fast exponentiation function (not used in current code)
ll power(ll x, ll n) {
  ll ans = 1;
  while (n > 0) {
    if (n & 1)
      ans = (ans * x);
    x = (x * x);
    n >>= 1;
  }
  return ans;
}

void solve() {
  int n, k;
  cin >> n >> k;
  vi a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vi mp(n + 1);  // frequency map for numbers
  for (int ele : a) {
    mp[ele]++;
  }
  vi prefixcnt(n + 1);  // prefix sum of counts
  for (int i = 1; i <= n; ++i) {
    prefixcnt[i] = prefixcnt[i - 1] + mp[i];
  }
  ll ans = 1;  // answer starts at 1 (minimum possible GCD)
  for (int gcd = 1; gcd <= n; ++gcd) {
    int temp = min(n, 4 * gcd - 1);  // upper limit for checking valid elements
    int good = n - prefixcnt[temp];  // count of numbers that are >= temp
    if (gcd <= n) {
      good += mp[gcd];    // add count of gcd itself
    }
    if (2 * gcd <= n) {
      good += mp[2 * gcd];  // add count of 2*gcd
    }
    if (3 * gcd <= n) {
      good += mp[3 * gcd];  // add count of 3*gcd
    }
    if (good >= n - k) {  // if enough valid elements
      ans = gcd;          // update max GCD
    }
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin.exceptions(cin.failbit);
  ll t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/