// Problem: CF 1060 A - Phone Numbers
// https://codeforces.com/contest/1060/problem/A

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long N = 11; // Length of a valid phone number (11 digits starting with '8')
  long len;
  std::string s;
  std::cin >> len >> s;
  long eights(0); // Count how many '8' digits are available
  for (long p = 0; p < s.size(); p++) {
    eights += (s[p] == '8'); // Increment count if current character is '8'
  }
  long ans = (s.size() / N); // Maximum possible phone numbers based on total cards
  ans = (ans < eights) ? ans : eights; // Limit by number of available '8's (required for phone numbers)
  std::cout << ans << std::endl;
  return 0;
}
/*
Flowerbox:
Problem: Phone Numbers
Purpose: Determine the maximum number of valid 11-digit phone numbers that can be formed,
         where each phone number starts with '8'. Each digit card can be used only once.
Algorithms/Techniques: Greedy approach - count available '8's and total digits.
Time Complexity: O(n), where n is the length of string s (we iterate through all characters once).
Space Complexity: O(1), only using a few variables regardless of input size.
*/

// https://github.com/VaHiX/codeForces/