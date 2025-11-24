// Problem: CF 1550 B - Maximum Cost Deletion
// https://codeforces.com/contest/1550/problem/B

/*
B. Maximum Cost Deletion
Algorithm: Greedy with optimal substring selection
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The problem involves deleting consecutive equal characters from a binary string to maximize points,
where deletion of a substring of length l gives a*l + b points. The key insight is:
- If b >= 0, it's always better to delete larger substrings (combine segments).
- If b < 0, we should avoid merging segments if it reduces total score.
We calculate the number of transitions between different characters in the string,
which tells us how many deletions we need at minimum. 
If b >= 0, we can merge all into one deletion. Otherwise, we compute based on number of transitions.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, a, b;
    std::cin >> n >> a >> b;
    std::string s;
    std::cin >> s;
    long d(0);
    // Count number of transitions between different characters
    for (long p = 1; p < s.size(); p++) {
      d += (s[p] != s[p - 1]);
    }
    // Decide how many operations to perform based on b value
    long factor = (b >= 0) ? n : (1 + (d + 1) / 2);
    printf("%ld\n", n * a + factor * b);
  }
}


// https://github.com/VaHiX/codeForces/