// Problem: CF 1335 C - Two Teams Composing
// https://codeforces.com/contest/1335/problem/C

/*
C. Two Teams Composing
Algorithm: 
- Count frequency of each skill using a map
- Find maximum frequency (mx) and number of distinct skills (d)
- The result is the minimum of:
  - d (number of distinct skills, for first team)
  - mx (maximum frequency, for second team)
  - If d == mx, then we can only use d - 1 because one student must be left out to satisfy both constraints

Time Complexity: O(n log n) due to map operations
Space Complexity: O(n) for storing the frequency map
*/

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::map<long, long> m; // Map to store frequency of each skill
    long n;
    scanf("%ld", &n);
    long mx(0); // Maximum frequency of any skill
    while (n--) {
      long a;
      scanf("%ld", &a);
      ++m[a]; // Increment frequency of skill 'a'
      mx = (mx > m[a]) ? mx : m[a]; // Update maximum frequency
    }
    long d(m.size()), res(0); // d = number of distinct skills, res = result
    if (d == mx) {
      res = d - 1; // If equal, we can't use all distinct skills due to constraint
    } else {
      res = (d < mx) ? d : mx; // Otherwise take minimum of both
    }
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/