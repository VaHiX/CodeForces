// Problem: CF 980 A - Links and Pearls
// https://codeforces.com/contest/980/problem/A

/*
 * Problem: A. Links and Pearls
 * 
 * Purpose: Determine if a necklace of links ('-') and pearls ('o') can be rearranged 
 *          such that the number of links between every two adjacent pearls is equal.
 * 
 * Algorithm:
 *   - Count total links ('-') and pearls ('o') in the string.
 *   - If there are no pearls, then it's always possible (return YES).
 *   - If there are pearls, check if the number of links is divisible by the number of pearls.
 *     This ensures equal spacing between adjacent pearls when rearranged.
 * 
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for counting.
 */

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long x(0), y(0);  // x: count of pearls ('o'), y: count of links ('-')
  for (long p = 0; p < s.size(); p++) {
    x += (s[p] == 'o');  // increment pearl count
    y += (s[p] == '-');  // increment link count
  }
  std::cout << (((x == 0) || (y % x == 0)) ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/