// Problem: CF 1915 D - Unnatural Language Processing
// https://codeforces.com/contest/1915/problem/D

/*
D. Unnatural Language Processing
Algorithm: Greedy syllable splitting based on vowel positions.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing indices of vowels.

The solution identifies all vowels ('a' and 'e') in the string and then uses a greedy approach to determine
syllable boundaries. A syllable is either:
- CV (consonant + vowel)
- CVC (consonant + vowel + consonant)

We process from left to right, and for each vowel we find, we try to form a valid syllable:
- If the next vowel is at position i+3 (that is, the current vowel is in middle of a CVC syllable),
  we include that consonant in the current syllable.
- Otherwise we form a CV syllable ending at that vowel.

The algorithm ensures correctness by processing vowels sequentially and building each syllable greedily
based on local structure. This works because all valid inputs follow specific grammar rules.
*/

#include <iostream>
#include <vector>
#include <string>

bool vowel(char x) { return (x == 'a' || x == 'e'); } // Check if character is a vowel

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<long> v; // Store indices of vowels in the string
    
    for (long p = 0; p < s.size(); p++) {
      if (vowel(s[p])) {  // If current character is a vowel, store its index
        v.push_back(p);
      }
    }
    
    for (long p = 0; p < v.size(); p++) {
      long idx = v[p];  // Index of current vowel
      
      std::cout << s[idx - 1] << s[idx];  // Print consonant and vowel forming CV syllable
      
      // Check if next vowel is 3 positions ahead (implies the current vowel is part of CVC)
      if (p + 1 < v.size() && v[p + 1] == idx + 3) {
        std::cout << s[idx + 1];  // Add middle consonant to current syllable
      } else if (idx + 2 == s.size()) {
        // If we have reached end of string and last character is a consonant,
        // we include it in the final syllable
        std::cout << s[idx + 1];
      }
      
      // Add dot separator between syllables except after the last one
      if (p + 1 < v.size()) {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/