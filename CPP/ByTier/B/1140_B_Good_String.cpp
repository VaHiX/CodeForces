// Problem: CF 1140 B - Good String
// https://codeforces.com/contest/1140/problem/B

/*
B. Good String
Algorithm: Greedy approach to find the minimum deletions required to make a string "good".
Time Complexity: O(n) where n is the length of the string (two passes through the string)
Space Complexity: O(1) - only using a few variables for counting

The problem involves determining the minimum number of characters to delete from a string of '<' and '>' 
so that it becomes "good", meaning we can reduce it to a single character by performing operations:
- Choosing '>' deletes the next character (if exists)
- Choosing '<' deletes the previous character (if exists)

Key insight: A string is good if there are no consecutive sequences of all '<' or all '>' that prevent
the possibility of reducing it to a single character. The minimum deletions needed equals 
the minimum count of consecutive '<'s at the start or consecutive '>'s at the end.

Approach:
1. Count the number of leading '<' characters (from left)
2. Count the number of trailing '>' characters (from right)
3. Return the minimum of these two counts as the answer
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long mn(s.size()), rem(0);
    // Count leading '<' characters
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '<') {
        ++rem;
      } else {
        break;
      }
    }
    mn = (mn < rem) ? mn : rem;
    rem = 0;
    // Count trailing '>' characters
    for (long p = s.size() - 1; p >= 0; p--) {
      if (s[p] == '>') {
        ++rem;
      } else {
        break;
      }
    }
    mn = (mn < rem) ? mn : rem;
    printf("%ld\n", mn);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/