// Problem: CF 1969 B - Shifts and Sorting
// https://codeforces.com/contest/1969/problem/B

/*
B. Shifts and Sorting
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm:
The problem involves making a binary string sorted in non-descending order using cyclic shifts of substrings.
The key insight is:
- We only need to focus on transitions from '1' to '0', because those are where we need to move a '0' to the left.
- For each such transition, we must perform operations that "move" the '0' backwards.
- A greedy approach is used: 
    - Count consecutive '1's before a '0'.
    - When encountering a '0', we can potentially move it forward by shifting a substring which includes both current and previous '1's.
    - The minimum cost for moving a '0' past all preceding '1's is the total length of the substring involved.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), only using a few variables for counting and tracking indices.

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long long cnt(0), a(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        // If we encounter a '0', add the cost of shifting it forward,
        // which is based on how many '1's are to its left.
        cnt += (a > 0) * (a + 1);
      } else {
        // Count consecutive '1's before encountering '0'.
        ++a;
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/