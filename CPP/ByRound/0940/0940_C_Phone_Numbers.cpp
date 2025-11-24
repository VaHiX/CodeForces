// Problem: CF 940 C - Phone Numbers
// https://codeforces.com/contest/940/problem/C

/*
Purpose: 
This code finds the lexicographically smallest string `t` of length `k` such that:
1. The set of letters in `t` is a subset of the set of letters in `s`.
2. `s` is lexicographically smaller than `t`.

Algorithm:
- First, we build a set of unique characters from string `s`.
- We initialize `t` with the first `k` characters of `s`.
- Then, we try to incrementally increase `t` to make it lexicographically greater than `s`.
- We iterate from the end of `t` towards the start to find the first character that can be increased.
- Once we find such a character, we increase it to the next available character in the set `g` and fill the rest of the string with the smallest character from `g`.

Time Complexity: O(n + k * log n)
Space Complexity: O(n + k)

Techniques:
- Set data structure for unique character tracking.
- Iterative approach to find the next lexicographically greater string.
*/

#include <iostream>
#include <set>
#include <iterator>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  std::set<char> g; // Set to store unique characters from s
  std::string t(""); // Result string initialized as empty
  for (long p = 0; p < n; p++) {
    g.insert(s[p]); // Insert all characters into the set
    if (p < k) {
      t += s[p]; // Initialize t with first k characters of s
    }
  }
  // Fill remaining positions in t with the smallest available character
  while (t.size() < k) {
    t += *g.begin();
  }
  // Try to make t lexicographically greater than s
  for (long p = k - 1; p >= 0 && k <= n; p--) {
    if (s[p] == *g.rbegin()) {
      continue; // Skip if current character is the largest in the set
    }
    char x = s[p];
    // Find the next character in the set that is greater than s[p]
    while (!g.count(++x))
      ;
    t[p] = x; // Replace character at position p
    // Fill all positions after p with the smallest character in the set
    for (long u = p + 1; u < k; u++) {
      t[u] = *g.begin();
    }
    break; // Break after finding the first valid change
  }
  std::cout << t << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/