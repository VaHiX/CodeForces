// Problem: CF 825 D - Suitable Replacement
// https://codeforces.com/contest/825/problem/D

/*
Algorithm/Technique: Greedy String Construction
Approach:
- We process the string `s` and try to fill `?` characters greedily.
- For each `?`, we determine which character to use by looking at the current position in `t`.
- If replacing `?` with `t[qm]` would reduce the count of that character below zero (i.e., we already used it too many times), we choose a different character from `t`.
- Otherwise, we simply assign `t[qm]`.
- The key idea is to avoid overusing letters in `t` that would prevent forming more copies of `t`.

Time Complexity: O(|s| + |t|)
Space Complexity: O(1) (since count array is fixed size 26)

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 26;
  std::string s, t;
  std::cin >> s >> t;
  std::vector<long> count(N, 0);  // Count of each character in s (excluding '?')
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == '?') {
      continue;
    }
    ++count[s[p] - 'a'];
  }
  long qm(0);  // Position in t to determine which character to use next
  long ind(0);  // Current index in s
  while (ind < s.size()) {
    if (s[ind] != '?') {
      ++ind;
      continue;
    }
    ++qm;
    qm %= t.size();  // Cycle through t characters
    if (count[t[qm] - 'a'] > 0) {
      --count[t[qm] - 'a'];  // If we can use t[qm], reduce its count
    } else {
      s[ind] = t[qm];  // Otherwise, assign t[qm] and don't reduce count
      ++ind;
    }
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/