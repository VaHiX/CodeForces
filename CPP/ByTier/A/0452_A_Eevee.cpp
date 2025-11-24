// Problem: CF 452 A - Eevee
// https://codeforces.com/contest/452/problem/A

/*
 * Problem: Eevee Evolution
 * 
 * Purpose: Given a pattern of known and unknown letters (represented by dots),
 * find the unique Pokémon name from a predefined list that matches the pattern.
 * 
 * Algorithms/Techniques:
 * - Brute-force matching: For each Pokémon name, check if it fits the given pattern.
 * - Pattern matching: Compare each character in the input pattern with the candidate name.
 * 
 * Time Complexity: O(N * M * K)
 *   - N: number of Pokémon names (8)
 *   - M: length of the pattern (input string length)
 *   - K: average number of characters compared per match check
 *   In this specific implementation, since N=8, it's effectively O(M) for practical purposes.
 * 
 * Space Complexity: O(1)
 *   - Only a fixed-size array of Pokémon names and a few variables are used.
 *   - No extra space grows with input size.
 */

#include <cstdio>
#include <iostream>
#include <string>

int main() {
  const int N = 8;
  std::string pokemons[] = {"vaporeon", "jolteon", "flareon", "espeon",
                            "umbreon",  "leafeon", "glaceon", "sylveon"};
  int n;
  scanf("%d\n", &n); // Read the length of the word
  std::string hidden;
  std::cin >> hidden; // Read the pattern with known letters and dots
  std::string output = ""; // To store the result
  for (int p = 0; p < N; p++) { // Iterate through each Pokémon name
    std::string current = pokemons[p];
    if (current.size() != n) { // Skip if length doesn't match
      continue;
    }
    bool possible = 1; // Assume it's a match initially
    for (int q = 0; q < n; q++) { // Check each character in the pattern
      if (hidden[q] != '.' && hidden[q] != current[q]) { 
        // If a known letter doesn't match, it's not a match
        possible = 0;
        break;
      }
    }
    if (possible) { // If it matches, we found the answer
      output = current;
      break;
    }
  }
  std::cout << output << std::endl; // Print the matching Pokémon
  return 0;
}


// https://github.com/VaHiX/CodeForces/