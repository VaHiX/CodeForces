// Problem: CF 1295 B - Infinite Prefixes
// https://codeforces.com/contest/1295/problem/B

/*
B. Infinite Prefixes
Algorithm: 
    - For each prefix of the infinite string t = ssss..., we compute its balance,
      which is defined as cnt_0 - cnt_1, where cnt_0 is number of 0s and cnt_1 is number of 1s.
    - Since t is infinite, we must use a periodic approach:
        * Compute prefix sums of the difference (0 - 1) for s to get the cumulative balances.
        * Track the minimum and maximum values of these balances.
        * If total sum of differences (t) is 0, then all balances repeat in cycle.
            - Check if x lies within [min, max]; if so, answer is -1 (infinite).
        * Else, for each unique balance value p, check how many full cycles can be added
          to reach a balance of x. This is done by checking if (x-p) is divisible by total sum and non-negative.

Time Complexity: O(n log n) per test case due to map usage
Space Complexity: O(n) for storing prefix sums in the map

Input:
    T - number of test cases.
    For each test case:
        n, x - length of string s, target balance.
        s - binary string.

Output:
    Number of prefixes with balance equal to x. If infinite, print -1.
*/
#include <iostream>
#include <map>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, x;
    std::cin >> n >> x;
    std::string s;
    std::cin >> s;
    std::map<long, long> cnt; // Map to store frequency of each prefix balance
    long t(0), mn(0), mx(0); // t = total balance of s, mn/mx = min/max balance seen
    for (long p = 0; p < s.size(); p++) {
      t += (s[p] == '0') - (s[p] == '1'); // Update running balance
      ++cnt[t]; // Count this balance
      mn = (mn < t) ? mn : t; // Track minimum balance
      mx = (mx > t) ? mx : t; // Track maximum balance
    }
    if (t == 0) { // If total balance is zero, the string repeats
      std::cout << ((mn <= x && x <= mx) ? "-1" : "0") << std::endl;
      continue;
    }
    long res(x == 0); // Start with count of 0-balance prefix (empty prefix)
    for (long p = mn; p <= mx; p++) { // For each unique balance
      long cur = x - p; // How much more to add to reach x
      res += cnt[p] * ((cur % t == 0) && ((cur / t) >= 0)); // Add valid combinations
    }
    std::cout << res << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/