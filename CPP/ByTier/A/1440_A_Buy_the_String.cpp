// Problem: CF 1440 A - Buy the String
// https://codeforces.com/contest/1440/problem/A

/*
 * Problem: A. Buy the String
 * Purpose: Given a binary string and costs for characters '0' and '1', as well as a cost to change characters,
 *          determine the minimum coins needed to buy the string after possibly changing some characters.
 * 
 * Algorithm:
 *   - For each character in the string, decide whether to keep it or change it to minimize total cost.
 *   - The strategy is to compare if it's cheaper to:
 *     1. Keep the current character (pay its original cost)
 *     2. Change it and then buy it (pay change cost + new character cost)
 *   - Optimization: Precompute minimum cost for '0' and '1' by comparing direct purchase vs. change + purchase.
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the string
 * Space Complexity: O(1), only using a constant amount of extra space
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, cz, cn, h;
    std::cin >> n >> cz >> cn >> h;
    
    // Optimize cost for '0' and '1': decide whether to keep or change
    cz = (cz < (cn + h)) ? cz : (cn + h);  // minimum cost to have a '0' (either buy it directly or change '1' to '0')
    cn = (cn < (cz + h)) ? cn : (cz + h);  // minimum cost to have a '1' (either buy it directly or change '0' to '1')
    
    std::string s;
    std::cin >> s;
    
    long total(0);
    for (long p = 0; p < s.size(); p++) {
      // Add the minimal cost for this character
      total += (s[p] == '0') ? cz : cn;
    }
    std::cout << total << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/