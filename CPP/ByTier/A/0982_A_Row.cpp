// Problem: CF 982 A - Row
// https://codeforces.com/contest/982/problem/A

/*
Purpose: Determine if a given seating arrangement on chairs is "maximal".
         A seating is maximal if no two people are adjacent and no more people can be seated without violating the adjacency rule.

Algorithms/Techniques: 
- Linear scan through the string to check adjacency constraints
- Special handling for edge cases (first and last positions)
- Check for possible placement of new person in middle positions

Time Complexity: O(n) - single pass through the string of length n
Space Complexity: O(1) - only using a constant amount of extra space (variables: n, s, valid, p)
*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  bool valid(true); // Assume seating is valid initially
  
  // Check for adjacent occupied seats
  for (long p = 1; p < s.size(); p++) {
    if (s[p - 1] == '1' && s[p] == '1') {
      valid = false;
      break;
    }
  }
  
  // Special case: if only one chair and it's empty, it's not maximal
  if (n == 1 && s[0] == '0') {
    valid = false;
  }
  
  // Check if the last two chairs are both empty - if so, a person can be seated there
  if (n >= 2 && s[n - 2] == '0' && s[n - 1] == '0') {
    valid = false;
  }
  
  // Check if the first two chairs are both empty - if so, a person can be seated there
  if (n >= 2 && s[0] == '0' && s[1] == '0') {
    valid = false;
  }
  
  // Check for a middle empty chair that can be filled (i.e., surrounded by empty seats)
  for (long p = 1; p < s.size() - 1; p++) {
    if (s[p - 1] == '0' && s[p] == '0' && s[p + 1] == '0') {
      valid = false;
      break;
    }
  }
  
  std::cout << (valid ? "Yes" : "No") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/