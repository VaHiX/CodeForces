// Problem: CF 1974 B - Symmetric Encoding
// https://codeforces.com/contest/1974/problem/B

/*
B. Symmetric Encoding

Purpose:
This program decodes a string that was encoded using a symmetric encoding scheme.
The encoding process involves:
1. Creating an auxiliary string 'r' with distinct characters of the input string, sorted alphabetically.
2. Replacing each character in the original string with its symmetric counterpart in 'r'.
   Symmetry is defined such that the first character maps to the last, second to second-last, etc.

Algorithm:
- For each test case:
  - Extract all unique characters from the input string and sort them.
  - Create a mapping from each character to its symmetric counterpart.
  - Replace each character in the input string using this mapping.

Time Complexity: O(n * log(n)) per test case due to sorting, but since there are at most 26 distinct characters,
                 the effective time complexity is effectively constant for sorting.
Space Complexity: O(1) for the auxiliary structures (as at most 26 characters), and O(n) for input/output strings.

Techniques:
- Use of std::map for character mapping
- Efficient use of boolean vector to track unique characters
- Symmetric mapping through reverse indexing
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string b;
    std::cin >> b;
    std::vector<bool> v(26, 0); // Track which characters are present
    for (long p = 0; p < n; p++) {
      v[b[p] - 'a'] = 1; // Mark character as seen
    }
    std::string a(""); // Store sorted unique characters
    for (long p = 0; p < 26; p++) {
      if (!v[p]) {
        continue; // Skip unused characters
      }
      a += (char)('a' + p); // Append character to result string
    }
    std::map<char, char> m; // Map each character to its symmetric counterpart
    for (long p = 0; p < a.size(); p++) {
      m[a[p]] = a[a.size() - 1 - p]; // Symmetric mapping: first <-> last, second <-> second-last
    }
    for (long p = 0; p < b.size(); p++) {
      b[p] = m[b[p]]; // Replace each character using the mapping
    }
    std::cout << b << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/