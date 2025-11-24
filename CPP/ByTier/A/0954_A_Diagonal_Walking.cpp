// Problem: CF 954 A - Diagonal Walking
// https://codeforces.com/contest/954/problem/A

/*
Algorithm: Greedy
Approach:
- Traverse the string from left to right.
- Whenever we find a pair of consecutive moves "RU" or "UR", we replace the second character with "D".
- This effectively reduces the length of the sequence by 1 for each such pair found.
- The process continues until no more such pairs exist.
- Time Complexity: O(n), where n is the length of the string.
- Space Complexity: O(1), excluding the input string storage.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  for (long p = 1; p < s.size(); p++) {
    // Check if current character is 'R' and previous is 'U' -> replace current with 'D'
    if (s[p] == 'R' && s[p - 1] == 'U') {
      s[p] = 'D';
      --n;
    } else if (s[p] == 'U' && s[p - 1] == 'R') {
      // Check if current character is 'U' and previous is 'R' -> replace current with 'D'
      s[p] = 'D';
      --n;
    }
  }
  std::cout << n << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/