// Problem: CF 1397 A - Juggling Letters
// https://codeforces.com/contest/1397/problem/A

/*
Problem: A. Juggling Letters
Purpose: Determine whether it's possible to make all n strings equal by moving characters between them.
Algorithm: Count total occurrences of each letter across all strings. For all strings to be made equal,
           each letter must appear a number of times divisible by n (so each string can have same count).
Time Complexity: O(S) where S is the sum of all string lengths.
Space Complexity: O(1) since we use fixed-size array of 26 elements.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const int N = 26; // Number of lowercase English letters
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<long> v(N, 0); // Count of each character across all strings
    for (long p = 0; p < n; p++) {
      std::string s;
      std::cin >> s;
      for (long u = 0; u < s.size(); u++) {
        ++v[s[u] - 'a']; // Increment count for character at index s[u] - 'a'
      }
    }
    bool res(true);
    for (long p = 0; p < N; p++) {
      if (v[p] % n) { // If count of any character is not divisible by n
        res = false;
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/