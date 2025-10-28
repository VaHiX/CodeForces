// Problem: CF 1030 C - Vasya and Golden Ticket
// https://codeforces.com/contest/1030/problem/C

/*
C. Vasya and Golden Ticket
Purpose: Determine if a given sequence of digits can be split into two or more non-intersecting segments with equal sums.

Algorithms/Techniques:
- Brute-force approach over possible segment sums (0 to 1000)
- For each candidate sum, attempt to partition the string into segments
  where each segment's digit sum equals the candidate

Time Complexity: O(N * M) where N is the length of string and M is the maximum possible sum (1000)
Space Complexity: O(1) - only using fixed-size variables

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  const long N = 1000;  // Maximum possible sum for a segment (since max digit is 9 and n <= 100)
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  bool possible(false);  // Flag to track if a valid partition exists

  // Try all possible sums for segments
  for (long p = 0; p <= N; p++) {
    long cur(0), cnt(0);  // cur: current segment sum, cnt: number of complete segments
    for (long q = 0; q < s.size(); q++) {
      cur += s[q] - '0';  // Add the digit to current segment sum
      if (cur > p) {
        break;  // If current sum exceeds target, this partition is invalid
      } else if (cur == p) {
        cur = 0;  // Reset current sum for next segment
        ++cnt;    // Increment number of completed segments
      }
    }
    // Check if we have at least two segments and the last segment is complete
    if ((cnt > 1) && (cur == 0)) {
      possible = true;
      break;
    }
  }

  std::cout << (possible ? "YES" : "NO") << std::endl;  // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/