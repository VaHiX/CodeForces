// Problem: CF 2121 E - Sponsor of Your Problems
// https://codeforces.com/contest/2121/problem/E

/*
 * Problem: E. Sponsor of Your Problems
 * Purpose: Given two integers l and r of the same length, find the minimum value of f(l,x) + f(x,r) 
 *          where x ranges from l to r. Here, f(a,b) counts the number of matching digits at each position.
 *
 * Algorithms/Techniques:
 * - String comparison and digit-by-digit analysis
 * - Greedy approach with branching logic for differing positions
 * - Optimization by checking how many initial digits match
 *
 * Time Complexity: O(n), where n is the length of the string representation of l and r.
 * Space Complexity: O(1) - only using a constant amount of extra space (variables and fixed-size structures).
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(0);
  long t;
  std::cin >> t;
  while (t--) {
    std::string l, r;
    std::cin >> l >> r;
    if (l == r) {
      // If l equals r, then f(l,x) + f(x,r) = 2*len, because x must equal l and r.
      std::cout << (2 * l.size()) << std::endl;
      continue;
    }
    long idx(0);
    // Find the index where the first difference occurs between l and r
    while (idx < l.size() && l[idx] == r[idx]) {
      ++idx;
    }
    // If we can increment the differing digit in l to get a value x such that 
    // x < r, then we might be able to reduce the number of mismatches.
    if (l[idx] + 1 < r[idx]) {
      std::cout << (2 * idx) << std::endl;
      continue;
    }
    // Otherwise, calculate the count based on current position and trailing digits
    long cnt(2 * idx + 1);
    for (long p = idx + 1; p < l.size(); p++) {
      // If there is a transition from '9' to '0', we add one more mismatch.
      if (l[p] == '9' && r[p] == '0') {
        ++cnt;
      } else
        break;
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/