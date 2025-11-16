// Problem: CF 837 A - Text Volume
// https://codeforces.com/contest/837/problem/A

/*
 * Problem: Text Volume
 * Description: Calculate the maximum number of capital letters in any word of a given text.
 * Algorithm: Iterate through the string, count capital letters per word, and track the maximum.
 * Time Complexity: O(n) where n is the length of the input string.
 * Space Complexity: O(n) for storing the input string.
 *
 * Techniques:
 * - Single pass through the string
 * - Tracking word-wise capital letter counts
 * - Using max function to update global maximum
 */

#include <cstdio>
#include <iostream>
#include <string>

int main() {
  long n;
  scanf("%ld\n", &n);  // Read the length of the text (not used in logic, but part of input)
  std::string s;
  getline(std::cin, s);  // Read the full line of text
  long word(0), text(0);  // word: current word's capital letter count, text: max capital letter count so far
  for (size_t p = 0; p < s.size(); p++) {
    if (s[p] == ' ') {  // When space is encountered, end of a word
      text = (text > word) ? text : word;  // Update global max if current word's count is higher
      word = 0;  // Reset current word count
    } else if ('A' <= s[p] && s[p] <= 'Z') {  // If character is uppercase
      ++word;  // Increment current word's capital letter count
    }
  }
  text = (text > word) ? text : word;  // Check the last word after loop ends
  std::cout << text << std::endl;  // Output the maximum capital letter count
  return 0;
}


// https://github.com/VaHiX/CodeForces/