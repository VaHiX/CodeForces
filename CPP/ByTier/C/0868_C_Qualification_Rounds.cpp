// Problem: CF 868 C - Qualification Rounds
// https://codeforces.com/contest/868/problem/C

/*
 * Problem: Qualification Rounds
 * 
 * Purpose: Determine if a subset of problems can be selected such that each team knows at most half of the selected problems.
 * 
 * Algorithm:
 * 1. For each problem, represent the set of teams that know it as a bitmask.
 * 2. Store unique bitmasks in a set to eliminate duplicate problem knowledge patterns.
 * 3. Check if there exists a pair of distinct problems (bitmasks) such that their bitwise AND is zero,
 *    which means no team knows both problems (i.e., no team is overloaded).
 * 
 * Time Complexity: O(n * k + m^2), where n is the number of problems, k is the number of teams, and m is the number of unique masks.
 * Space Complexity: O(m), where m is the number of unique masks stored.
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::set<long> s;
  for (long p = 0; p < n; p++) {
    long x(0);  // x will store the bitmask for current problem
    for (long q = 0; q < k; q++) {
      long b;
      scanf("%ld", &b);
      x = 2 * x + b;  // Build the binary number from left to right
    }
    s.insert(x);  // Insert the bitmask into the set to get unique problem patterns
  }
  std::vector<long> v;
  for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
    v.push_back(*it);  // Transfer unique masks to a vector for easier access
  }
  bool possible(*s.begin() == 0);  // If the smallest mask is 0, then at least one team knows no problems (trivial case)
  for (long p = 0; p < v.size(); p++) {
    if (possible) {
      break;
    }
    for (long q = p + 1; q < v.size(); q++) {
      if ((v[p] & v[q]) == 0) {  // If bitwise AND is zero, no team knows both problems
        possible = true;
        break;
      }
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/