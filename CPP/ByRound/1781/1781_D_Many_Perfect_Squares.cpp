// Problem: CF 1781 D - Many Perfect Squares
// https://codeforces.com/contest/1781/problem/D

/*
 * Problem: D. Many Perfect Squares
 *
 * Algorithm/Technique:
 * - The approach uses a mathematical property to find x such that a_i + x is a perfect square.
 * - For a number to be a perfect square, it can be expressed as t^2.
 * - If a_i + x = t^2, then x = t^2 - a_i.
 * - We analyze differences between pairs of numbers in the array (a_j - a_i).
 * - For each such difference d, we check all divisors q of d.
 * - Using the condition that q and d/q have the same parity (both odd or both even),
 *   we derive potential x values using the formula: x = (d/q - q) / 2.
 * - We use a map to count how many times each x leads to a perfect square in the set.
 *
 * Time Complexity:
 * - For each pair (i, j), we iterate through all divisors of (a_j - a_i).
 * - Since we are dealing with a_j - a_i up to 10^9, the number of divisors is at most sqrt(10^9) ≈ 31623.
 * - Total complexity is O(n^2 * sqrt(max_diff)) ≈ O(50^2 * 31623) ≈ O(1e8), acceptable within time limits.
 *
 * Space Complexity:
 * - Map stores at most O(n^2) elements in worst case, but practically much less.
 * - Overall space is O(n^2).
 */

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    long long a[100];
    cin >> n;
    map<int, int> mp;
    int ans = 1;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int s = a[j] - a[i];
        for (int q = 1; q * q <= s; q++)
          if (q % 2 == s / q % 2 && s % q == 0) {
            long long x = (s / q - q) / 2;
            if (x * x >= a[i]) {
              mp[x]++;
              ans = max(ans, mp[x] + 1); // Add 1 because current pair contributes to count
            }
          }
      }
      mp.clear(); // Clear map for next iteration to avoid interference
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/