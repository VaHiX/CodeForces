// Problem: CF 801 A - Vicious Keyboard
// https://codeforces.com/contest/801/problem/A

/*
Purpose: This code solves the problem of maximizing the number of "VK" substrings in a string 
by changing at most one character. It uses a greedy approach to first count all existing "VK" 
substrings, then tries to optimize by possibly changing one character to increase the count.

Algorithms/Techniques: Greedy algorithm, string traversal, substring counting

Time Complexity: O(n), where n is the length of the input string. We iterate through the string twice.
Space Complexity: O(1), as we use only a constant amount of extra space (excluding input string).

The approach:
1. First pass: Identify and count all "VK" substrings, mark them as 'x' to avoid double counting.
2. Second pass: Try to find an optimal position to change one character to potentially create 
   a new "VK" substring (either by converting "VV" to "VK" or "KK" to "VK").
*/

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long count(0);
  bool changed(false);
  for (long p = 1; p < s.size(); p++) {
    if (s[p - 1] == 'V' && s[p] == 'K') {
      ++count;
      s[p - 1] = s[p] = 'x'; // Mark this "VK" as counted
    }
  }
  for (long p = 1; p < s.size(); p++) {
    if ((s[p - 1] == 'V' && s[p] == 'V') || (s[p - 1] == 'K' && s[p] == 'K')) {
      ++count;
      break; // Found a potential spot to insert a 'K' after a 'V' or a 'V' after a 'K'
    }
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/