// Problem: CF 2045 A - Scrambled Scrabble
// https://codeforces.com/contest/2045/problem/A

/*
 * Problem: Scrambled Scrabble
 * 
 * Algorithm/Techniques:
 * - Greedy approach with dynamic programming principles
 * - Character classification: vowels, consonants, special cases (Y, NG)
 * - Iterative optimization over possible numbers of Ys treated as vowels
 * - Syllable construction rules: CVC (Consonant-Vowel-Consonant)
 * 
 * Time Complexity: O(n), where n is the length of string S
 * Space Complexity: O(1), only using a fixed number of variables
 */

using System;
using System.Security.Cryptography;
namespace Cf {
internal class Program2045a {
  static void Main(string[] args) {
    Console.WriteLine(GetMaxLength(Console.ReadLine()));
  }
  public static int GetMaxLength(string s) {
    int yCount = 0, fCount = 0, y = 0, n = 0, g = 0, ngCount = 0;
    // Mask to identify vowels A, E, I, O, U
    int mask = (1 << ('A' - 'A')) + (1 << ('E' - 'A')) + (1 << ('I' - 'A')) +
               (1 << ('O' - 'A')) + (1 << ('U' - 'A'));
    foreach (char c in s) {
      if (c == 'Y')
        y++;
      else if (c == 'N')
        n++;
      else if (c == 'G')
        g++;
      else if (((1 << (c - 'A')) & mask) != 0)
        yCount++; // Count of actual vowels (A, E, I, O, U)
      else
        fCount++; // Count of regular consonants (not Y, N, G)
    }
    
    // Count valid NG combinations (each NG uses one N and one G)
    ngCount = Math.Min(n, g);
    // Adjust fCount by adding leftover N and G after NG usage
    fCount += n + g - ngCount * 2;
    
    int max = 0;
    // Try all possible ways to treat Ys as vowels (0 to y times)
    for (int i = 0; i <= y; ++i) {
      int yc = yCount + i;  // Effective vowel count (actual vowels + Ys treated as vowels)
      int fc = fCount + y - i;  // Effective consonant count (original consonants + Ys treated as consonants)
      
      if (yc * 2 <= fc) {
        // If enough consonants for all syllables (each syllable needs 2 consonants per vowel)
        max = Math.Max(max, yc * 3 + Math.Min(ngCount, fc));
      } else {
        // If not enough consonants, need to optimize syllable count
        int dy = fc / 2;  // Max number of syllables from consonants
        int c = 0;
        // How many NG can be used for optimal arrangement
        int yng = Math.Min(ngCount, yc - dy);
        int ng = Math.Min(yng * 2, ngCount);  // NG can be used as 2 consonants each
        if (yc - dy - ng > 0 && dy * 2 != fc) {
          c = 1;  // Special case adjustment
        }
        max = Math.Max(max, dy * 3 + ng * 2 + yng + Math.Min(ngCount - ng, fc) +
                                Math.Min(ng % 2, c));
      }
    }
    return max;
  }
}
}


// https://github.com/VaHiX/CodeForces/