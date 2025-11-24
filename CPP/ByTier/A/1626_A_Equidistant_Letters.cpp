// Problem: CF 1626 A - Equidistant Letters
// https://codeforces.com/contest/1626/problem/A

/*
Algorithm/Technique: Sorting
Time Complexity: O(n log n) where n is the length of the string, due to the sorting step.
Space Complexity: O(1) if we do not count the input string's space, otherwise O(n) to store the string.

The approach sorts the characters in the string lexicographically. Since we are only required to
rearrange the letters such that pairs of characters appearing exactly twice are equidistant,
sorting ensures that all characters are in order, which satisfies the condition in a simple way.
This works because any valid arrangement can be achieved by sorting, and the problem allows us
to output any valid arrangement.
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end());  // Sort the characters in ascending order
    std::cout << s << std::endl;  // Output the sorted string
  }
}


// https://github.com/VaHiX/CodeForces/