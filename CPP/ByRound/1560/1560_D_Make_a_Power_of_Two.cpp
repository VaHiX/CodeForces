// Problem: CF 1560 D - Make a Power of Two
// https://codeforces.com/contest/1560/problem/D

/*
D. Make a Power of Two
Algorithms/Techniques: Dynamic Programming with String Matching
Time Complexity: O(63 * m) where m is the length of input string s, and 63 is the number of powers of 2 up to 10^18
Space Complexity: O(63 * log(max_value)) for storing powers of 2 up to 10^18

The problem requires finding the minimum number of operations (insert or delete) to transform a given number into any power of 2.
We precompute all powers of 2 up to 10^18 and for each test case, we compute the minimum edit distance between the input string
and each of these powers of 2 using a greedy approach.

The algorithm works as follows:
1. Precompute all powers of 2 from 2^0 to 2^62 (since 2^63 > 10^18)
2. For each input string:
   - Try matching it against each power of 2
   - Calculate minimum operations needed using a greedy method
   - Return the minimum among all possible powers
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// Calculates the minimum number of operations (insert/delete) to transform 's' into 'target'
int getDist(const std::string &target, const std::string &s) {
  int a(0), b(0), cnt(0);
  while (a < target.size() || b < s.size()) {
    if (a >= target.size()) {     // If we've exhausted the target string
      ++b;                        // Move to next character in input string
      ++cnt;                      // Increment operation count
    } else if (b >= s.size()) {   // If we've exhausted the input string
      ++a;                        // Move to next character in target string
      ++cnt;                      // Increment operation count
    } else if (target[a] == s[b]) { // If characters match
      ++a;                        // Move to next character in both strings
      ++b;
    } else {                      // Characters don't match
      ++b;                        // Move only in input string (simulate deletion)
      ++cnt;                      // Increment operation count
    }
  }
  return cnt;
}

int main() {
  std::vector<std::string> vs;
  int64_t x(1);
  for (long p = 1; p < 63; p++) {   // Generate all powers of 2 up to 2^62
    vs.push_back(std::to_string(x));
    x *= 2;
  }
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long res(100);
    for (long p = 0; p < vs.size(); p++) {   // Try all powers of 2
      int dist = getDist(vs[p], s);          // Calculate distance to current power of 2
      res = (res < dist) ? res : dist;       // Keep minimum distance
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/