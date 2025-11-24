// Problem: CF 722 B - Verse Pattern
// https://codeforces.com/contest/722/problem/B

/*
 * Purpose: Determine if a given text matches a specified verse pattern based on syllable counts.
 * 
 * Algorithm:
 *   - For each line in the input text:
 *     * Count the total number of vowels in all words of that line.
 *     * Compare this count with the corresponding value in the verse pattern.
 *   - If all lines match their respective pattern values, output "YES"; otherwise, output "NO".
 * 
 * Time Complexity: O(n * m), where n is the number of lines and m is the average length of a line.
 * Space Complexity: O(1) excluding input storage, as we only use a fixed amount of extra variables.
 * 
 * Techniques: 
 *   - Character-by-character vowel counting in strings.
 *   - Direct comparison of cumulative vowel counts with pattern values.
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

bool isVowel(char c) {
  // Check if the character is a vowel (case-insensitive)
  return (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') ||
         (c == 'y') || (c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') ||
         (c == 'U') || (c == 'Y');
}

int main() {
  int n;
  scanf("%d\n", &n); // Read number of lines
  std::vector<int> pat(n);
  for (int p = 0; p < n; p++) {
    scanf("%d ", &pat[p]); // Read the pattern for each line
  }
  scanf("\n"); // Consume the newline after the pattern
  bool res(true); // Initialize result as true
  for (int p = 0; p < n; p++) {
    std::string s;
    getline(std::cin, s); // Read the entire line
    int count(0); // Initialize vowel counter
    for (int a = 0; a < s.size(); a++) {
      count += isVowel(s[a]); // Add 1 if the character is a vowel
    }
    if (count != pat[p]) {
      res = false; // If mismatch, set result to false
      break; // No need to check further
    }
  }
  puts(res ? "YES" : "NO"); // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/