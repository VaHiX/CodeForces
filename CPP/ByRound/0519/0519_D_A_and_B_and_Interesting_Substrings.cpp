// Problem: CF 519 D - A and B and Interesting Substrings
// https://codeforces.com/contest/519/problem/D

/*
Algorithm: Prefix Sum with Hash Map
Approach:
- For each character in the string, maintain a map of prefix sums ending at that character.
- A valid substring contributes to the result if:
  1. It starts and ends with the same character.
  2. The sum of values of characters between the start and end (excluding the first and last) is zero.
- This is equivalent to finding pairs of indices where the prefix sum is the same, and the character at those indices is the same.
- We use a map to store the frequency of each prefix sum for each character encountered so far.
- Time Complexity: O(n), where n is the length of the string.
- Space Complexity: O(n), for storing prefix sums in maps for each character.

*/

#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
  const int64_t N = 26;
  std::vector<int64_t> v(N);
  for (int64_t p = 0; p < N; p++) {
    std::cin >> v[p];
  }
  std::string s;
  std::cin >> s;
  std::vector<std::map<int64_t, int64_t>> a(N); // Map to store prefix sum frequencies for each character
  int64_t sofar(0), total(0); // sofar: current prefix sum; total: result count
  for (int64_t p = 0; p < s.size(); p++) {
    int64_t current = s[p] - 'a'; // Get index of current character
    if (a[current].count(sofar) > 0) {
      // If the prefix sum 'sofar' has been seen before for the same character,
      // it means there exists a valid substring ending here
      total += a[current][sofar];
    }
    sofar += v[current]; // Update prefix sum
    if (a[current].count(sofar) > 0) {
      // Increment frequency of this prefix sum for current character
      ++a[current][sofar];
    } else {
      // Initialize frequency of this prefix sum for current character
      a[current][sofar] = 1;
    }
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/