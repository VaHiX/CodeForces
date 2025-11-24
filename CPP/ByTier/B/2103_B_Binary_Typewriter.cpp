// Problem: CF 2103 B - Binary Typewriter
// https://codeforces.com/contest/2103/problem/B

/*
 * Problem: B. Binary Typewriter
 * Purpose: Find the minimum number of operations to type a binary string,
 *          considering that we may reverse at most one substring.
 * 
 * Algorithm:
 * - The cost of typing a string is determined by the number of transitions between '0' and '1'.
 * - Initially, finger is on '0'.
 * - Each time we encounter a different character from previous one, it costs 1 operation to move finger.
 * - Additionally, we can reverse one substring to reduce cost.
 * 
 * Key Insight:
 * - If the string doesn't change much (fewer transitions), reversing can be beneficial.
 * - But we only get benefit if we reduce transitions by 2 or more.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    // Count number of transitions in the string
    long inv(s[0] == '1');  // Start with 1 if first character is '1'
    for (long p = 1; p < s.size(); p++) {
      inv += (s[p - 1] != s[p]);  // Increment if adjacent characters are different
    }
    // Adjust the count based on specific rules:
    // If transitions = 2, then we can reduce to 1 because of initial position
    // If transitions > 2, subtract 2 since reversing can save 2 operations at most
    if (inv == 2) {
      inv = 1;
    } else if (inv > 2) {
      inv -= 2;  // We potentially saved two moves due to reversal
    }
    // Total operations = length of string + number of transitions adjusted
    std::cout << (s.size() + inv) << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/