// Problem: CF 1674 B - Dictionary
// https://codeforces.com/contest/1674/problem/B

/*
B. Dictionary
Purpose: This program determines the lexicographical index of a two-letter Berland word in a dictionary that contains all valid words (words with two different lowercase letters) ordered lexicographically.

Algorithm:
- For each word consisting of two different lowercase letters, calculate its position in the dictionary.
- Words are ordered such that:
  1. First letter determines the group (a to z).
  2. Within a group, second letter determines order (b to z, excluding the first letter).
- Formula used:
  - Index = 1 + 25 * (first_letter - 'a') + (second_letter - 'a') - (second_letter > first_letter)
  - This accounts for all words before the current word's group and within the group.

Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1), only using a constant amount of extra space.

Input Format:
- First line contains integer t (number of test cases).
- Each of the next t lines contains a string s (a valid Berland word of two different lowercase letters).

Output Format:
- For each test case, print the index of the word in the dictionary.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Calculate the position in the dictionary
    // 1: base offset
    // 25 * (s[0] - 'a'): number of words from previous groups
    // (s[1] - 'a'): position within current group, starting from 0
    // -(s[1] > s[0]): correct for the fact that second letter cannot equal first letter in a valid word
    long res = 1 + 25 * (s[0] - 'a') + (s[1] - 'a') - (s[1] > s[0]);
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/