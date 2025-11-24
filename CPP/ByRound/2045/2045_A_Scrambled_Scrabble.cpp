// Problem: CF 2045 A - Scrambled Scrabble
// https://codeforces.com/contest/2045/problem/A

/*
 * Problem: A. Scrambled Scrabble
 * Purpose: Given a string of uppercase English letters, determine the maximum length 
 *          of a word that can be formed using valid syllable structures (consonant-vowel-consonant).
 * 
 * Algorithms/Techniques:
 *   - Character counting and classification into vowels, consonants, or special cases (Y)
 *   - Greedy strategy based on constraints derived from syllable formation rules
 *   - Mathematical optimization to compute maximum number of valid syllables
 *
 * Time Complexity: O(n), where n is the length of input string S
 * Space Complexity: O(1), only using a fixed amount of additional variables
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  string a;
  cin >> a;
  
  // Counters for different types of characters:
  // e = number of vowels (A,E,I,O,U)
  // y = number of Ys
  // b = number of consonants (excluding N,G, and Y)
  // n = number of N's
  // g = number of G's
  int y = 0, g = 0, n = 0, e = 0, b = 0;
  
  // Classify each character in the input string
  for (const char &i : a) {
    if (i == 'A' || i == 'E' || i == 'O' || i == 'U' || i == 'I')
      ++e; // vowel
    else if (i == 'Y')
      ++y;  // Y can be used as either vowel or consonant, we will evaluate how to use it optimally
    else
      ++b; // regular consonant (not N, G, Y)
    n += i == 'N'; 
    g += i == 'G';
  }

  // Compute optimal assignment of Ys: determine how many Ys should be treated as vowels
  const int y1 = max(min((2 * e + 2 * y - b + 2) / 3, y), 0); // this formula ensures valid balance
  
  // Adjust counts based on choosing y1 Y's as vowels
  b += y1;        // increase consonants since we treat some Ys as consonants
  e += y - y1;    // decrease vowels and increase with remaining Ys treated as vowels

  // Calculate how many complete syllables can be formed
  g = min({g, n, e * 2, max(b - e * 2, b & 1)}); // compute maximum number of valid syllables allowed by constraints
  
  // Output final length: each syllable contributes 3 characters, plus additional compensation
  cout << g + 3 * min((b - g) / 2, e);
  
  return 0;
}


// https://github.com/VaHiX/codeForces/