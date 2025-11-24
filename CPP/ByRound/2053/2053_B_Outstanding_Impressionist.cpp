// Problem: CF 2053 B - Outstanding Impressionist
// https://codeforces.com/contest/2053/problem/B

/*
B. Outstanding Impressionist
Time Complexity: O(n log n) per test case due to sorting and binary search operations.
Space Complexity: O(n) for storing vectors and sets.

Algorithms/Techniques:
- Set usage for tracking unique values.
- Binary search via std::lower_bound to efficiently find range matches.
- Logic to determine uniqueness based on intervals and value overlaps.

Each impression is represented by an interval [l_i, r_i].
An impression i is unique if there exists a way to assign values to all impressions such that:
- w_i is distinct from all other w_j (j != i),
- w_i lies in [l_i, r_i],
- All w_j lie in their respective intervals.

The solution identifies values that are common to multiple intervals (overlap)
and determines if each interval can still be made unique by ensuring its range 
does not overlap with others beyond the necessary constraints.
*/
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> vl(n), vr(n);
    std::set<long> fs, gs; // fs: set of values that appear in intervals, gs: values appearing in intervals with only one element (self overlap)
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &vl[p], &vr[p]);
      if (vl[p] == vr[p]) { // Single-element interval
        if (fs.count(vl[p])) {
          gs.insert(vl[p]); // Already seen -> conflict, mark as needing exclusion
        } else {
          fs.insert(vl[p]); // First time seeing the value
        }
      }
    }
    std::vector<long> dv;
    for (std::set<long>::iterator it = fs.begin(); it != fs.end(); it++) {
      dv.push_back(*it); // Convert set to sorted vector for binary search
    }
    for (long p = 0; p < n; p++) {
      if (vl[p] == vr[p]) { // Single element interval
        printf("%c", gs.count(vl[p]) ? '0' : '1'); // If the value is in conflict, not unique ('0'), else it's unique ('1')
      } else { // Multi-element interval
        std::vector<long>::iterator ita =
            std::lower_bound(dv.begin(), dv.end(), vl[p]); // First element >= vl[p]
        std::vector<long>::iterator itb =
            std::lower_bound(dv.begin(), dv.end(), vr[p]); // First element >= vr[p]
        printf("%c", (fs.count(vl[p]) && fs.count(vr[p]) &&
                              (itb - ita == vr[p] - vl[p])
                          ? '0'
                          : '1')); // If all values in range are present and count matches the actual interval size, then not unique
      }
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/