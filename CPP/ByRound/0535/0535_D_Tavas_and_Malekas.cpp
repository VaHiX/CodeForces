// Problem: CF 535 D - Tavas and Malekas
// https://codeforces.com/contest/535/problem/D

/*
D. Tavas and Malekas
Algorithm/Techniques: String matching, Sliding window, Modular arithmetic
Time Complexity: O(n + m)
Space Complexity: O(1)

The problem involves determining how many possible strings s of length n can exist given:
- A pattern p of length |p|
- A subsequence of positions where p occurs in s
We must count the number of valid strings that could match this pattern and subsequence.

Approach:
1. Process each position in the given subsequence to check consistency with the pattern.
2. For overlapping matches, verify that characters align properly.
3. Count how many free characters remain after accounting for all constraints.
4. Each free character can be any of 26 lowercase letters -> answer is 26^(free_chars) mod MOD
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  const ll N = 26;
  const ll MOD = 1000000007;
  std::ios_base::sync_with_stdio(false);
  ll n, m;
  std::cin >> n >> m;
  std::string t;
  std::cin >> t;
  ll last(-1), cnt(n); // cnt counts free characters, initialized to total length
  bool possible(true);
  while (m--) {
    long x;
    std::cin >> x;
    if (last < 0 || x >= last + t.size()) {
      // No overlap with previous match, subtract full pattern length
      cnt -= t.size();
    } else {
      // Overlapping case: check if the overlapping part is consistent with pattern
      if (t[x - last] != t[0]) {
        possible = false;
        break;
      } else {
        // Overlap is valid; subtract only the difference
        cnt -= (x - last);
      }
    }
    last = x;
  }
  if (possible) {
    ll prod(1);
    while (cnt--) {
      prod *= N;
      prod %= MOD;
    }
    std::cout << prod << std::endl;
  } else {
    std::cout << "0" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/