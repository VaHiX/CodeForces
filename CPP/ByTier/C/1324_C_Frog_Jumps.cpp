// Problem: CF 1324 C - Frog Jumps
// https://codeforces.com/contest/1324/problem/C

/*
C. Frog Jumps
Algorithm: Greedy with sliding window approach
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables

The problem asks to find the minimum jump distance 'd' such that a frog can traverse 
from position 0 to position n+1, obeying character constraints at each position. 

The approach is essentially finding the maximum contiguous segment of 'L's or 'R's
that cannot be crossed with current d, and then setting d to this max gap.
We simulate the process where we track last R position, and compute gaps between R's,
ensuring that no segment exceeds the allowed jump distance.

*/
#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    s += 'R'; // Add a sentinel R to handle the last segment easily
    long mx(0), last(-1); // mx stores max gap, last tracks previous R position
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'L') {
        continue; // Skip L positions, only care about R's to determine gaps
      }
      long diff = p - last; // Calculate gap between current R and previous R
      last = p; // Update last R position
      mx = (mx > diff) ? mx : diff; // Keep track of maximum gap
    }
    printf("%ld\n", mx); // Print the minimum required jump distance
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/