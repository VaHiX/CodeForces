// Problem: CF 1163 B2 - Cat Party (Hard Edition)
// https://codeforces.com/contest/1163/problem/B2

/*
B2. Cat Party (Hard Edition)
Purpose: Find the largest number x such that in the first x days, we can remove exactly one day 
         so that all remaining ribbon colors have the same number of occurrences.

Algorithms/Techniques:
- Sliding window approach with map to track color frequencies
- Check valid conditions for streaks by examining frequency distribution
- Time complexity: O(n^2) in worst case due to nested checks, Space complexity: O(n)

Time Complexity: O(n^2)
Space Complexity: O(n)
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

bool check(std::map<long, long> &m, long val) {
  bool disagree(false);
  for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
    if (it->second == val) {
      continue;
    }
    if ((it->second == val + 1) || (it->second == 1)) {
      if (disagree) {
        return false;
      }
      disagree = true;
    } else {
      return false;
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
  long res(0);
  for (long p = 0; p < n; p++) {
    long col = a[p];
    ++m[col]; // Add current color to frequency map
    long cnt = m.size(); // Number of distinct colors so far
    if (cnt == 1) {
      res = p + 1; // All colors are same, valid streak
    } else if (cnt >= p) {
      res = p + 1; // More distinct colors than days seen - not a valid case without checking further
    } else if ((p % cnt == 0) && check(m, p / cnt)) {
      res = p + 1; // Check if division of total elements by unique count gives consistent frequencies
    } else if ((p % (cnt - 1) == 0) && check(m, p / (cnt - 1))) {
      res = p + 1; // Check alternate condition related to removing one element and checking remaining frequencies
    }
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/