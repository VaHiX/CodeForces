// Problem: CF 518 A - Vitaly and Strings
// https://codeforces.com/contest/518/problem/A

/*
Purpose: To find a string that is lexicographically between two given strings s and t.
         The solution increments the last character of s and checks if the result is still
         less than t. If it is, it outputs the result; otherwise, it outputs "No such string".

Algorithm:
    1. Read two strings s and t.
    2. Create a copy of string s called med.
    3. Starting from the last character, increment the character:
       - If it's 'z', set it to 'a' and continue to the next character.
       - Otherwise, increment it and stop.
    4. Check if the new string med is lexicographically smaller than t.
       - If yes, print med.
       - Else, print "No such string".

Time Complexity: O(n), where n is the length of the strings.
Space Complexity: O(n), for storing the strings.

Techniques:
    - Character manipulation
    - Lexicographical comparison
*/

#include <iostream>
#include <string>

int main() {
  std::string first;
  getline(std::cin, first);
  std::string second;
  getline(std::cin, second);
  std::string med(first);
  for (int p = first.size() - 1; p >= 0; p--) {
    if (med[p] == 'z') {
      med[p] = 'a';
    } else {
      ++med[p];
      break;
    }
  }
  bool possible(0);
  for (int p = 0; p < med.size(); p++) {
    if (med[p] < second[p]) {
      possible = 1;
      break;
    }
  }
  if (possible) {
    std::cout << med << std::endl;
  } else {
    std::cout << "No such string" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/