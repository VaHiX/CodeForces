// Problem: CF 1380 B - Universal Solution
// https://codeforces.com/contest/1380/problem/B

/*
 * Purpose: This program determines the optimal sequence of choices (R, P, S) 
 *          to maximize the average number of wins against a Rock-Paper-Scissors 
 *          bot whose behavior is determined by a fixed string and a starting index.
 *          The bot cycles through the string and makes its move based on the characters.
 *          The strategy is to choose the move that beats the most frequent character 
 *          in the string, ensuring maximum average wins.
 *
 * Algorithm: 
 *   1. Count frequencies of 'R', 'S', and 'P' in the string.
 *   2. Choose the character that beats the most frequent one (i.e., the one 
 *      that is not beaten by the most frequent character).
 *   3. Output a string of the same length as input, filled with the chosen character.
 *
 * Time Complexity: O(n) where n is the length of the string. We loop through 
 *                  the string once to count characters and once to output.
 *
 * Space Complexity: O(n) for storing the output string of size n.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;                                 // Number of test cases
  std::cin >> t;
  while (t--) {
    std::string s;                          // Input string
    std::cin >> s;
    long x(0), y(0), z(0);                  // Counters for P, R, S
    for (long p = 0; p < s.size(); p++) {   // Count occurrences of each character
      if (s[p] == 'P') {
        ++x;
      } else if (s[p] == 'R') {
        ++y;
      } else if (s[p] == 'S') {
        ++z;
      }
    }
    long u(0);                              // Max count among P, R, S
    char c;                                 // Character that beats the most frequent
    if (x >= y && x >= z) {                 // If P is the most frequent
      u = x;
      c = 'S';                              // Choose S to beat P (S beats P)
    } else if (y >= x && y >= z) {          // If R is the most frequent
      u = y;
      c = 'P';                              // Choose P to beat R (P beats R)
    } else if (z >= x && z >= y) {          // If S is the most frequent
      u = z;
      c = 'R';                              // Choose R to beat S (R beats S)
    }
    std::string t(s.size(), c);             // Create output string with same length
    std::cout << t << std::endl;            // Print result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/