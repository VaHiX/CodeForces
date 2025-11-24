// Problem: CF 1943 F - Minimum Hamming Distance
// https://codeforces.com/contest/1943/problem/F

/*
F. Minimum Hamming Distance
Algorithm: Dynamic Programming with prefix/suffix analysis and sliding window techniques.
Time Complexity: O(n^2) per test case, where n is the length of strings s and t.
Space Complexity: O(n) for auxiliary arrays and vectors.

The problem asks to find the minimum Hamming distance between a given binary string t
and any "good" binary string g. A good string g satisfies that every prefix of g has at least
half the elements as mode (i.e., more frequent character). The solution uses preprocessing
to compute valid prefixes and suffixes, then dynamic programming with sliding window optimization.
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;
const int oo = 1e9;

// Convert '0' -> -1 and '1' -> 1 for easier computation
void sgnify(string &s) {
  for (auto &i : s) {
    if (i == '0')
      i = -1;
    else
      i = 1;
  }
}

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  string t;
  cin >> t;
  
  // Transform both strings: 0 -> -1, 1 -> 1
  sgnify(s);
  sgnify(t);

  // Sum of t gives us a hint on which sign our solution should take
  int sum = 0;
  for (auto i : t)
    sum += i;
  
  // If sum is positive, make everything negative, so that sum becomes negative
  if (sum > 0) {
    sum = -sum;
    for (auto &i : s)
      i = -i;
    for (auto &i : t)
      i = -i;
  }

  vector<bool> bad(n + 1); // Mark positions where we can't make good prefix
  vi p(n + 1);             // Prefix sums
  const int LIM = n + 2;

  // Compute prefix sums of transformed t
  p[0] = LIM;
  for (int i = 0; i < n; ++i)
    p[i + 1] = t[i] + p[i];

  vi pref = p, suf = p; // Copy to compute min/max

  // Compute prefix minimums from left
  for (int i = 1; i <= n; ++i)
    pref[i] = min(pref[i], pref[i - 1]);

  // Compute suffix maximums from right
  for (int i = n - 1; i >= 0; --i)
    suf[i] = max(suf[i + 1], suf[i]);

  // Identify bad positions where no good prefix exists up to that point
  for (int i = 0; i < n; ++i)
    if (s[i] == 1)
      bad[i] = pref[i] > suf[i + 1];

  bad[n] = 1;

  // First bad position marker in reverse way
  vi firstbad(LIM * 2 + 1, n);
  int at = 2 * LIM;
  
  for (int i = 0; i < n; ++i)
    if (bad[i]) {
      while (at > p[i + 1]) {
        firstbad[at--] = i;
      }
    }

  vi dp(n + 1, oo); // dp[i] = min cost to reach position i

  // Initialize dp with base case (if start is bad)
  for (int i = 0; i <= n; ++i)
    if (bad[i]) {
      dp[i] = 0;
      break;
    }

  // Dynamic Programming step: fill out valid transitions
  for (int i = 0; i < n; ++i)
    if (bad[i] and dp[i] != oo) {
      int k = i, zeros = 0;
      
      // For each ending position j, track count of zeros
      for (int j = i; j < n; ++j) {
        zeros += t[j] == -1;

        // Calculate required extra ones based on balance between prefixes/suffixes
        int e = (pref[i] - suf[j + 1] + 1) / 2;

        // Adjust k to maintain valid zero constraints via sliding window
        while (zeros > e) {
          zeros -= t[k++] == -1;
        }

        // Compute new minimum value of prefix at j+1 with optimal balance from k onwards
        int nwminimum = p[j + 1] - (j + 1 - k) + (p[k] - pref[k]);

        // Find nearest valid state to update DP table
        int to = firstbad[max(0, nwminimum)];

        dp[to] = min(dp[to], dp[i] + e);
      }
    }

  // Final result is the minimum between direct computation and dp[n]
  cout << min((-sum + 1) / 2, dp[n]) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/