// Problem: CF 1451 C - String Equality
// https://codeforces.com/contest/1451/problem/C

#include <iostream>
#include <vector>
#include <string>

/*
 * Problem: C. String Equality
 *
 * Purpose: Determine if string 'a' can be transformed into string 'b' using two types of operations:
 *          1. Swap adjacent characters.
 *          2. Increment a contiguous substring of length k, if all characters are not 'z'.
 *
 * Algorithm: 
 *   - For each character from 'a' to 'z', calculate the difference in counts between 'a' and 'b'.
 *   - For each position, check if we can "push" excess characters to the next position,
 *     ensuring divisibility by k to maintain valid operations.
 *
 * Time Complexity: O(N) where N is the length of the strings (since there are at most 26 characters).
 * Space Complexity: O(1) since we use fixed-size arrays (27 elements each).
 */
int main() {
  const long N = 26;
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string sa, sb;
    std::cin >> sa >> sb;
    // from[i] stores count of characters in 'a' minus count in 'b', for each character a-z
    std::vector<long> from(N + 1, 0), to(N + 1, 0);
    for (long p = 0; p < sa.size(); p++) {
      ++from[sa[p] - 'a'];
    }
    for (long p = 0; p < sb.size(); p++) {
      ++to[sb[p] - 'a'];
    }
    bool possible(true);
    for (long p = 0; p < N; p++) {
      // If there are fewer characters in 'a' than in 'b', transformation is impossible
      if (from[p] < to[p]) {
        possible = false;
        break;
      }
      // Adjust the count: subtract how many we need for 'b'
      from[p] -= to[p];
      // If remaining count isn't divisible by k, it's not valid due to group increment rules
      if (from[p] % k) {
        possible = false;
        break;
      }
      // Push excess count to the next character to simulate operations
      from[p + 1] += from[p];
    }
    std::cout << (possible ? "Yes" : "No") << std::endl;
  }
}

// https://github.com/VaHiX/codeForces/