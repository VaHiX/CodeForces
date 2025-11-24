// Problem: CF 1818 A - Politics
// https://codeforces.com/contest/1818/problem/A

/*
 * Problem: Politics
 * 
 * Purpose:
 *   Given n members and k opinions, each member has a stance (+ or -) for each opinion.
 *   Before the debate, we can expel any number of members (except ourselves).
 *   After all k opinions are discussed, members leave based on majority rule in each round.
 *   Goal: Maximize the number of remaining members (including self) after final round.
 *
 * Algorithm:
 *   - For each test case:
 *     1. Read n and k
 *     2. Read stances for all n members
 *     3. For each member from index 1 onwards, check if they agree with the first member on all k opinions
 *        - If not, they will be expelled to avoid conflict in later rounds (as we want to maximize staying)
 *     4. Count how many members stay (including self) and output result
 *
 * Time Complexity: O(n * k)
 * Space Complexity: O(n * k) due to storing the strings and vector of booleans
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::vector<bool> stay(n, 1); // Initially assume everyone stays
    std::vector<std::string> gn(n);
    for (long p = 0; p < n; p++) {
      std::cin >> gn[p]; // Read each member's stance
    }
    // Compare all members with the first one (index 0)
    for (long p = 1; p < n; p++) {
      for (long q = 0; q < k; q++) {
        if (gn[p][q] != gn[0][q]) { // If stance differs
          stay[p] = 0; // This member will be expelled to avoid conflicts
        }
      }
    }
    long res(1); // Start with 1 since we always stay
    for (long p = 1; p < n; p++) {
      res += stay[p]; // Add members who don't get expelled
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/