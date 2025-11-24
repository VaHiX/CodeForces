// Problem: CF 1971 B - Different String
// https://codeforces.com/contest/1971/problem/B

/*
 * Problem: Rearrange characters of a string to form a different string, if possible.
 * Algorithm: 
 *   - If the string has only one character, it's impossible to make a different string.
 *   - Otherwise, scan the string from left to right. If any character differs from the first,
 *     swap it with the first character to form a new string.
 *   - If all characters are the same, it's impossible to create a different string.
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(1), as we are modifying the string in-place.
 */

#include <stddef.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MOD 1000000007
#define set_precision(n) cout << fixed << setprecision(n);
typedef long long ll;
typedef unsigned long long ull;

// Fast exponentiation function
ll power(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a);
    a = (a * a);
    b = b >> 1;
  }
  return res;
}

// Generate all subsequences (not used in final solution)
void subs(string s, int i, string curr, vector<vector<ll>> &v) {
  if (i == s.size()) {
    vector<ll> vv;
    for (ll j = 0; j < curr.size(); j++) {
      vv.push_back(ll(curr[j] - '0'));
    }
    v.push_back(vv);
    return;
  }
  subs(s, i + 1, curr + s[i], v);
  subs(s, i + 1, curr, v);
}

// Check if a number is prime (not used in final solution)
bool isprime(ll n) {
  if (n == 1)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (ll i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

// Logarithm base conversion (not used in final solution)
ll log_a_to_base_b(ll a, ll b) {
  return (a > b - 1) ? 1 + log_a_to_base_b(a / b, b) : 0;
}

// Some function (not used in final solution)
ll func(ll n) {
  if (n == 0)
    return 0;
  ll t = sqrt(n);
  ll sum = (t - 1) * 3;
  ll tt = (n - (t * t)) / t + 1;
  sum += tt;
  return sum;
}

// Main logic for solving the problem
void solve() {
  string s;
  cin >> s;
  ll n = s.size();
  if (n == 1) {
    cout << "NO\n";
    return;
  } else {
    // Look for a character different from the first one
    for (ll i = 1; i < n; i++) {
      if (s[i] != s[0]) {
        // Swap the first character with this different one
        char c = s[i];
        s[i] = s[0];
        s[0] = c;
        cout << "YES\n";
        cout << s << endl;
        return;
      }
    }
  }
  // If all characters are the same, no rearrangement possible
  cout << "NO\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  set_precision(10);
  ll t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/