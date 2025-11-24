// Problem: CF 1245 C - Constanze's Machine
// https://codeforces.com/contest/1245/problem/C

/*
C. Constanze's Machine
Algorithms/Techniques: Dynamic Programming, Fibonacci-like sequence, String parsing
Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(n) for the precomputed Fibonacci array and input string storage

Problem Description:
The machine converts input letters to output. Special cases:
- 'm' becomes "nn" 
- 'w' becomes "uu"
All other letters remain unchanged.
We need to count how many valid original strings could produce a given output string.

Approach:
1. Precompute Fibonacci-like sequence where f[i] = f[i-1] + f[i-2], with base cases f[1] = 1, f[2] = 2
   This represents the number of ways to parse consecutive 'u's or 'n's
2. Parse input string:
   - If we encounter 'm' or 'w', return 0 (invalid)
   - For consecutive 'u's and 'n's, calculate how many combinations are possible using precomputed values
   - Multiply all valid combinations together for final answer
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  std::vector<ll> f(1e5 + 7, 0);
  f[1] = 1;  // Base case for Fibonacci-like sequence
  f[2] = 2;  // Base case for Fibonacci-like sequence
  for (long p = 3; p < f.size(); p++) {
    f[p] = f[p - 1] + f[p - 2];  // Compute next Fibonacci number with modulo
    f[p] %= MOD;
  }
  std::string s;
  std::cin >> s;
  ll cnt(1), tmp(0);
  for (ll p = 0; p < s.size(); p++) {
    if (s[p] == 'm' || s[p] == 'w') {
      cnt = 0;  // Invalid character encountered, no valid string
      break;
    } else if (s[p] == 'u') {
      ++tmp;  // Count consecutive 'u's
      if (p + 1 == s.size() || s[p + 1] != s[p]) {
        cnt *= f[tmp];  // Multiply accumulated result by number of ways to parse these 'u's
        cnt %= MOD;
        tmp = 0;  // Reset counter
      }
    } else if (s[p] == 'n') {
      ++tmp;  // Count consecutive 'n's
      if (p + 1 == s.size() || s[p + 1] != s[p]) {
        cnt *= f[tmp];  // Multiply accumulated result by number of ways to parse these 'n's
        cnt %= MOD;
        tmp = 0;  // Reset counter
      }
    }
  }
  std::cout << cnt << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/