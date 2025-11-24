// Problem: CF 2086 E - Zebra-like Numbers
// https://codeforces.com/contest/2086/problem/E

/*
E. Zebra-like Numbers
Algorithm: Dynamic Programming with Memoization
Time Complexity: O(log^2(r) * k) per query, where log(r) is the number of bits in r.
Space Complexity: O(k * log(r)) due to memoization table.

The problem involves counting integers in a range [l,r] whose "zebra value" equals k.
Zebra-like numbers have alternating bits in binary (starting with 1), such as 1, 5 (101), 21 (10101).
The zebra value of x is the minimum number of zebra-like numbers that sum to x.

This solution uses recursive dynamic programming:
- The function `query(n, k)` counts how many ways we can express n as a sum of exactly k zebra-like numbers.
- Precomputed base values are used to determine the decomposition structure.
- Binary search and prefix sums (using memoization) allow efficient queries on ranges.

*/

#include <iostream>
#include <map>

using namespace std;
const int N = 1e5 + 5;
using ll = long long;
map<ll, ll> mp[130]; // Memoization table for dp states
ll base[35];         // Precomputed powers of 4+1 used to build zebra-like numbers

// Query function: returns the count of ways to represent n using exactly k zebra-like numbers
ll query(ll n, ll k) {
  if (k >= 130 || k <= 0 || n == 0)
    return 0;
  if (mp[k].find(n) != mp[k].end())   // If already computed, return stored result
    return mp[k][n];
  
  long long ans = 0, c;
  ll now = 30;
  while (base[now] > n) {      // Find the largest valid base <= n
    now--;
  }
  c = base[now];               // Get current base value

  // Try all possible multiples of 'c' (which is a zebra-like number)
  for (ll i = 0; i <= n; i += c) {
    if (i + c <= n)
      ans += query(c - 1, k - i / c);   // Recurse using remaining value and reduced count
    else
      ans += query(n % c, k - i / c);   // Handle last segment
    if (k - i / c == 0)
      ans++;                            // If we've used exactly k zebra-like numbers, increment
  }

  mp[k][n] = ans;               // Store result for future use
  return ans;
}

int main() {
  base[0] = 1;                  // Initialize base array with first value
  for (int i = 1; i < 31; i++) { // Build powers of 4 + 1 up to 30
    base[i] = base[i - 1] * 4 + 1;
  }

  int T;                        // Number of test cases
  cin >> T;
  while (T--) {
    ll l, r, k;
    cin >> l >> r >> k;         // Read input parameters
    cout << query(r, k) - query(l - 1, k) << '\n'; // Output difference in range
  }
}


// https://github.com/VaHiX/codeForces/