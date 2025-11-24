// Problem: CF 877 A - Alex and broken contest
// https://codeforces.com/contest/877/problem/A

/*
 * Problem: Determine if a problem name contains exactly one of Alex's friends' names.
 * 
 * Approach:
 * - For each friend name ("Danil", "Olya", "Slava", "Ann", "Nikita"), use std::string::find()
 *   to locate all occurrences in the problem name.
 * - Count total occurrences across all names.
 * - Output "YES" if exactly one occurrence is found, otherwise "NO".
 * 
 * Time Complexity: O(n * m), where n is the length of the problem name string,
 *                    and m is the average length of the friend names (constant <= 6).
 * Space Complexity: O(1), only using a constant amount of extra space for variables.
 */

#include <iostream>
#include <string>
int main() {
  std::string s;
  std::cin >> s;
  int count(0), pos(0);
  pos = 0;
  // Find all occurrences of "Danil" and count them
  while ((pos = s.find("Danil", pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  pos = 0;
  // Find all occurrences of "Olya" and count them
  while ((pos = s.find("Olya", pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  pos = 0;
  // Find all occurrences of "Slava" and count them
  while ((pos = s.find("Slava", pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  pos = 0;
  // Find all occurrences of "Ann" and count them
  while ((pos = s.find("Ann", pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  pos = 0;
  // Find all occurrences of "Nikita" and count them
  while ((pos = s.find("Nikita", pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  // Output result based on whether exactly one occurrence was found
  std::cout << (count == 1 ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/