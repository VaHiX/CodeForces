// Problem: CF 1702 C - Train and Queries
// https://codeforces.com/contest/1702/problem/C

/*
C. Train and Queries

Problem Description:
Given a train route consisting of n stations (with possible duplicates), determine for k queries whether it's possible to travel from station a_j to station b_j. The train moves only in one direction along the route, from left to right.

Algorithms/Techniques:
- Preprocessing: For each unique station value, store the first and last occurrence index in the route.
- Query Processing: For each query (a, b), check if:
    1. Station a exists in the route (first occurrence is valid)
    2. Station b exists in the route (last occurrence is valid)
    3. First occurrence of a is less than or equal to last occurrence of b
    This ensures that a can reach b following the train's path.

Time Complexity:
- Preprocessing: O(n) for scanning and building maps
- Query Processing: O(k) for k queries
- Overall: O(n + k) per test case, where n and k are up to 2e5

Space Complexity:
- O(n) for storing the first and last indices for each unique station in the route
*/

#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> s(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &s[p]);
    }
    std::map<long, long> first, last;
    for (long p = 0; p < n; p++) {
      last[s[p]] = p;                     // Update the last occurrence of station s[p]
      if (first.count(s[p]) == 0) {       // If this is the first time seeing s[p]
        first[s[p]] = p;                  // Record its first occurrence
      }
    }
    while (k--) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      bool res = (first.count(x)) && (last.count(y)) && (first[x] <= last[y]);
      puts(res ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/