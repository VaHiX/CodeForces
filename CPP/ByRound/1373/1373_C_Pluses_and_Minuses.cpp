// Problem: CF 1373 C - Pluses and Minuses
// https://codeforces.com/contest/1373/problem/C

/*
C. Pluses and Minuses
Algorithm: Greedy with prefix sum optimization
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1)

The problem simulates a process where we track a running sum (cur) of '+' and '-' operations,
and for each failed attempt (when cur < 0), we increment the result counter by the index + 1.
The optimization avoids simulating all infinite attempts by directly tracking when we need to "shift"
the starting point and accumulate those steps.

Key technique: Prefix sum analysis with early termination logic.
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    ll cur(0), add(0), res(s.size()); // cur: current balance, add: how many shifts we made, res: result initialized with string length
    for (ll p = 0; p < s.size(); p++) {
      cur += (s[p] == '+') - (s[p] == '-'); // update running balance (increment for +, decrement for -)
      if (add + cur < 0) { // if the cumulative effect of shifts and current position causes negative value
        res += (p + 1);    // add steps needed to recover (from this index onwards)
        ++add;             // increment shift count (simulate resetting starting point)
      }
    }
    std::cout << res << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/