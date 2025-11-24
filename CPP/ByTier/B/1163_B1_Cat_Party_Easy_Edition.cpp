// Problem: CF 1163 B1 - Cat Party (Easy Edition)
// https://codeforces.com/contest/1163/problem/B1

/*
B1. Cat Party (Easy Edition)
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

This problem is same as the next one, but has smaller constraints.
Shiro's just moved to the new house. She wants to invite all friends of her to the house so they can play monopoly. However, her house is too small, so she can only invite one friend at a time.
For each of the n days since the day Shiro moved to the new house, there will be exactly one cat coming to the Shiro's house. The cat coming in the i-th day has a ribbon with color u_i. Shiro wants to know the largest number x, such that if we consider the streak of the first x days, it is possible to remove exactly one day from this streak so that every ribbon color that has appeared among the remaining x - 1 will have the same number of occurrences.

Algorithms/Techniques:
- Sliding window approach with map for frequency tracking
- For each prefix, we check if removing one element can make all remaining elements have equal frequencies
- Two checks for possible uniform distributions after removal: 
  * All colors appear (cnt) times except possibly one which appears (cnt+1) times.
  * All colors appear (cnt) times except possibly one (which appears 1 time).

Time Complexity: O(n^2) in worst case due to nested loop and map operations.
Space Complexity: O(n) for storing the map and vector.

*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

bool check(std::map<long, long> &m, long val) {
  bool disagree(false);
  // Iterate through all color frequencies in the map
  for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
    if (it->second == val) {
      // This frequency matches target, continue
      continue;
    }
    if ((it->second == val + 1) || (it->second == 1)) {
      // This is either one more than target or exactly 1 - possible exception
      if (disagree) {
        return false; // Already found an exception, not valid
      }
      disagree = true;
    } else {
      return false; // Invalid frequency
    }
  }
  return disagree;
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::map<long, long> m;
  long res(0); // Result stores the maximum valid streak
  for (long p = 0; p < n; p++) {
    long col = a[p];
    ++m[col]; // Add current color to frequency map
    
    long cnt = m.size(); // Current number of distinct colors
    
    if (cnt == 1) {
      // Only one color, valid streak
      res = p + 1;
    } else if (cnt >= p) {
      // More colors than days processed - all could be single occurrences, so it's a valid case
      res = p + 1;
    } else if ((p % cnt == 0) && check(m, p / cnt)) {
      // Check if we can evenly distribute by removing one entry and distributing remaining equally
      res = p + 1;
    } else if ((p % (cnt - 1) == 0) && check(m, p / (cnt - 1))) {
      // Check alternate division where one color is left with 1 occurrence
      res = p + 1;
    }
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/