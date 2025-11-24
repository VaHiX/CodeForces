// Problem: CF 747 B - Mammoth's Genome Decoding
// https://codeforces.com/contest/747/problem/B

/*
B. Mammoth's Genome Decoding
Purpose: Decode a DNA string by replacing '?' characters such that the counts of A, C, G, T are equal.
Algorithm: 
    1. Check if n is divisible by 4; if not, output "===" immediately.
    2. Count occurrences of A, C, G, T in the given string.
    3. Verify that no nucleotide count exceeds target (n/4).
    4. Calculate how many of each nucleotide need to be added to reach the target.
    5. Replace '?' characters with required nucleotides.
Time Complexity: O(n), where n is the length of the DNA string
Space Complexity: O(n), for storing the vector of replacement characters and the result string

Input:
- n (integer): Length of genome string (4 <= n <= 255)
- s (string): Genome string with characters from {A, C, G, T, ?}

Output:
- Valid decoded genome string if possible, otherwise "==="

Examples:
Input: 8
       AG?C??CT
Output: AGACGTCT

Input: 4
       AGCT
Output: AGCT

Input: 6
       ????G?
Output: ===

Input: 4
       AA??
Output: ===
*/

#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  size_t n;
  std::cin >> n;
  std::string dna;
  std::cin >> dna;
  long a(0), c(0), g(0), t(0);
  long target = n / 4;
  bool possible(true);
  if (n % 4 > 0) { // If length is not divisible by 4, impossible to split equally
    possible = 0;
  } else {
    for (size_t p = 0; p < dna.size(); p++) { // Count each nucleotide
      if (dna[p] == 'A') {
        ++a;
      } else if (dna[p] == 'C') {
        ++c;
      } else if (dna[p] == 'G') {
        ++g;
      } else if (dna[p] == 'T') {
        ++t;
      }
    }
  }
  if (a > target || c > target || g > target || t > target) { // If any count exceeds target
    possible = false;
  }
  if (possible) {
    std::vector<char> v; // Vector to hold required nucleotides for replacement
    a = target - a;
    c = target - c;
    g = target - g;
    t = target - t;
    while (a--) {        // Add missing 'A' characters
      v.push_back('A');
    }
    while (c--) {        // Add missing 'C' characters
      v.push_back('C');
    }
    while (g--) {        // Add missing 'G' characters
      v.push_back('G');
    }
    while (t--) {        // Add missing 'T' characters
      v.push_back('T');
    }
    size_t ind(0);
    for (int p = 0; p < dna.size(); p++) { // Replace '?' with required nucleotides
      if (dna[p] != '?') {
        continue;
      }
      dna[p] = v[ind++]; // Assign next required character from vector
    }
  }
  std::cout << (possible ? dna : "===") << std::endl; // Output result or "===" if impossible
  return 0;
}


// https://github.com/VaHiX/codeForces/