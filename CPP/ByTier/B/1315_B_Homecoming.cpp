// Problem: CF 1315 B - Homecoming
// https://codeforces.com/contest/1315/problem/B

/*
 * Problem: B. Homecoming
 * Purpose: Find the earliest crossroad Petya can walk to such that he can reach the last crossroad using public transport.
 * Algorithm: Greedily process from right to left, determining whether a segment of same type stations (all A or all B) can be covered with one ticket.
 * Time Complexity: O(n) where n is the length of string s
 * Space Complexity: O(1) excluding input storage
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long a, b, g;         // a = cost of bus ticket, b = cost of tram ticket, g = Petya's money
    std::cin >> a >> b >> g;
    std::string s;
    std::cin >> s;
    
    // Modify the last character to simplify loop logic
    s.back() = '_';
    
    long start(1);        // Initialize the starting crossroad index
    
    // Traverse from right to left to determine minimal walk index
    for (long p = s.size() - 2; p >= 0; p--) {
      if (s[p] == s[p + 1]) {
        continue;       // Skip if current and next are same type
      }
      
      // Deduct cost of ticket for moving from p to end
      g -= (s[p] == 'A' ? a : b);
      
      // If we run out of money, we must have started walk before this point
      if (g < 0) {
        start = p + 2;
        break;
      }
    }
    
    std::cout << start << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/