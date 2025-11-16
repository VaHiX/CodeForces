// Problem: CF 1996 E - Decode
// https://codeforces.com/contest/1996/problem/E

/*
 * Problem: E. Decode
 * 
 * Purpose: Given a binary string s, count the number of substrings where the number of 0s equals the number of 1s,
 *          for all possible intervals [l, r]. The result is the sum over all such intervals.
 * 
 * Algorithm:
 *   - Use a prefix sum technique with offset to transform the problem into counting equal prefix sums.
 *   - Map the binary string into a difference array where '0' contributes -1 and '1' contributes +1.
 *   - Use a frequency map to track how many times each prefix sum has occurred.
 *   - For each position, check how many previous positions have the same prefix sum, which indicates a valid substring.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(n), due to the arrays and maps used.
 * 
 * Techniques:
 *   - Prefix Sum
 *   - Hash Map (frequency counting)
 *   - Offset technique for handling negative indices
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define endl '\n'
#define int long long
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
string s;

void solve() {
  cin >> s;
  int n = s.size();
  s = " " + s; // Add a leading space to make indexing from 1
  vector<int> a(n + 1, 0), f(2 * n + 1, -1); // a: prefix sum array, f: frequency map of prefix sums (offset by n)

  // Compute prefix sums: 0 -> -1, 1 -> +1
  for (int i = 1; i <= n; i++) {
    if (s[i] == '0')
      a[i] = a[i - 1] - 1;
    else
      a[i] = a[i - 1] + 1;
  }

  int ans = 0, dis = n; // dis is offset to avoid negative indices
  f[dis] = 1; // Initially, prefix sum 0 occurs once at index 0

  // Process each position
  for (int i = 1; i <= n; i++) {
    // If we have seen the same prefix sum before, it means a valid substring exists
    if (f[a[i] + dis] != -1) {
      // Add the number of such substrings ending at this position
      (ans += (f[a[i] + dis]) * (n - i + 1)) %= mod;
      // Update the frequency with current index
      (f[a[i] + dis] += i + 1) % mod;
    } else {
      // First occurrence of the prefix sum
      f[a[i] + dis] = i + 1;
    }
  }
  cout << ans << endl;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/