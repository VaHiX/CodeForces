// Problem: CF 877 B - Nikita and string
// https://codeforces.com/contest/877/problem/B

/*
Algorithm: Dynamic Programming + Enumeration
Purpose: Find the maximum length of a "beautiful" string that can be formed by deleting characters from the input string. A beautiful string is one that can be split into three parts:
    - First part: only 'a'
    - Second part: only 'b'
    - Third part: only 'a'

Time Complexity: O(n^2), where n is the length of the string.
Space Complexity: O(n), for the prefix arrays va and vb.

Approach:
1. Precompute prefix sums of 'a' and 'b' characters.
2. Enumerate all possible splits into three parts (x, y) where:
   - [0, x): first part (all 'a')
   - [x, y): second part (all 'b')
   - [y, n): third part (all 'a')
3. For each split, compute the total length of valid parts.
4. Track the maximum valid length.

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long n = s.size();
  std::vector<long> va(n + 1, 0), vb(n + 1, 0);
  // Build prefix sums for 'a' and 'b'
  for (long p = 1; p <= n; p++) {
    va[p] = va[p - 1] + (s[p - 1] == 'a');
    vb[p] = vb[p - 1] + (s[p - 1] == 'b');
  }
  long maxSize(0);
  // Enumerate all possible splits into three parts
  for (long x = 0; x <= n; x++) {
    for (long y = x; y <= n; y++) {
      // Calculate total length of beautiful string:
      // va[x] = count of 'a' in [0, x)
      // (vb[y] - vb[x]) = count of 'b' in [x, y)
      // (va[n] - va[y]) = count of 'a' in [y, n)
      long totalSize = va[x] + (vb[y] - vb[x]) + (va[n] - va[y]);
      maxSize = (maxSize > totalSize) ? maxSize : totalSize;
    }
  }
  std::cout << maxSize << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/