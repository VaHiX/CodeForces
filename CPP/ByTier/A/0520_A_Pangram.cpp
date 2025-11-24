// Problem: CF 520 A - Pangram
// https://codeforces.com/contest/520/problem/A

/*
 * Problem: A. Pangram
 * Purpose: Check if a given string contains all letters of the English alphabet at least once.
 * Algorithm: Use a set to store unique characters from the input string. Convert uppercase letters to lowercase.
 *            If the size of the set equals 26 (number of letters in the alphabet), then it's a pangram.
 * Time Complexity: O(n), where n is the length of the input string. Each character is processed once.
 * Space Complexity: O(1), since the set will contain at most 26 characters (size of the alphabet).
 */

#include <cstdio>
#include <iostream>
#include <set>
#include <string>

int main() {
  const int N = 26;  // Number of letters in the English alphabet
  int n;
  scanf("%d\n", &n);  // Read the number of characters
  std::set<char> s;  // Set to store unique characters
  std::string input;
  getline(std::cin, input);  // Read the input string
  for (int p = 0; p < input.size(); p++) {  // Iterate through each character
    char c = input[p];
    if ('A' <= c && c <= 'Z') {  // Check if character is uppercase
      c += 'a' - 'A';  // Convert to lowercase
    }
    s.insert(c);  // Insert character into set (duplicates are ignored)
  }
  puts(s.size() == N ? "YES" : "NO");  // Print YES if all 26 letters are present
  return 0;
}


// https://github.com/VaHiX/CodeForces/