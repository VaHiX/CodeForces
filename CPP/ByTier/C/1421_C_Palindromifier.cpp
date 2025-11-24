// Problem: CF 1421 C - Palindromifier
// https://codeforces.com/contest/1421/problem/C

// Purpose: Transform a given string into a palindrome using at most 30 operations.
//          Two types of operations are allowed:
//          - L i: Append the substring s[1..i-1] reversed to the front
//          - R i: Append the substring s[i..n-1] reversed to the end
//
// Algorithm:
//          1. First, use R operation with i = n-1 to append the reverse of s[2..n-1] to the end.
//          2. Then, use L operation with i = n to append the reverse of s[1..n-1] to the front.
//          3. Finally, use L operation with i = 2 to append the reverse of s[1] to the front.
//
// Time Complexity: O(n) for reading the string and O(1) for operations, overall O(n)
// Space Complexity: O(n) for storing the string

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  std::cout << 3 << std::endl;
  std::cout << "R " << (s.size() - 1) << std::endl;
  std::cout << "L " << s.size() << std::endl;
  std::cout << "L 2" << std::endl;
}


// https://github.com/VaHiX/CodeForces/