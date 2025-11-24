// Problem: CF 1988 B - Make Majority
// https://codeforces.com/contest/1988/problem/B

/*
Algorithm/Techniques: Greedy approach with counter tracking
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) using only a few variables for counting

The problem asks whether we can reduce a binary string to a single '1' using operations 
that replace a subsegment with the majority element of that subsegment.

Key Insight:
If we have more 1s than 0s in the entire string, then it's possible to reduce it to a single '1'.
This is because we can always merge segments such that the majority element ends up being 1, 
as long as the total count of 1s is strictly greater than 0s.

We use two counters:
- a: counts number of 1s
- z: counts number of 0s

In the loop, we iterate through the string. For each position p:
- If s[p] is '1', increment a
- If s[p] is '0' and s[p-1] is '1', increment z

This logic is used to detect and count transitions from 1 to 0 in order to track valid 0s which can be merged.

Finally, we compare a and z:
- if a > z, it means there are more 1s than 0s in the string and it's possible to reduce to [1]
- otherwise, it's not possible
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
    long z(s[0] == '0'), a(s[0] == '1');
    for (long p = 1; p < n; p++) {
      if (s[p] == '1') {
        ++a;
      } else if (s[p - 1] == '1') {
        ++z;
      }
    }
    puts(a > z ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/CodeForces/