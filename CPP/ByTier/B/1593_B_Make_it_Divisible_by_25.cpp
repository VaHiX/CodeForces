// Problem: CF 1593 B - Make it Divisible by 25
// https://codeforces.com/contest/1593/problem/B

/*
B. Make it Divisible by 25
Purpose: Given a positive integer n, find the minimum number of digits to remove to make the remaining number divisible by 25.
Approach: 
- A number is divisible by 25 if its last two digits form a number divisible by 25.
- The valid endings for divisibility by 25 are: 00, 25, 50, 75.
- For each possible ending (00, 25, 50, 75), we check from right to left in the input string to find if a valid pair of digits exists.
- The number of operations needed is the total length minus the number of digits in the valid ending plus the count of removed digits between them.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) as we use fixed-size vector and variables

Algorithms/Techniques: 
- Greedy approach with checking valid endings
- Two-pointer technique from right to left

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::vector<std::string> v; // Store valid endings for divisibility by 25
  v.push_back("00"); // ending 00
  v.push_back("25"); // ending 25
  v.push_back("50"); // ending 50
  v.push_back("75"); // ending 75
  long t;
  std::cin >> t;
  while (t--) {
    std::string n;
    std::cin >> n;
    long res(n.size() + 1); // Initialize result with a large value
    for (long p = 0; p < v.size(); p++) { // For each valid ending
      bool first(false), second(false); // Flags to track if we found the two digits of the ending
      long cnt(0); // Count of digits to remove between the pair
      for (long i = n.size() - 1; i >= 0; i--) { // Traverse from right to left
        if (!first && n[i] == v[p][1]) { // If we haven't found second digit yet and current is second digit
          first = true;
        } else if (first && n[i] == v[p][0]) { // If we have found second digit, then check for first digit of ending
          second = true;
          break; // We found the pair, so we're done with this possible ending
        } else {
          ++cnt; // Increment count for removal since current digit is not part of the valid ending
        }
      }
      if (!second) { // If we didn't find a complete valid ending
        cnt = n.size(); // Then remove all digits
      }
      res = (res < cnt) ? res : cnt; // Update minimum operations needed
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/