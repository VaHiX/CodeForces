// Problem: CF 499 B - Lecture
// https://codeforces.com/contest/499/problem/B

/*
 * Problem: Lecture
 * 
 * Purpose:
 *   This program translates a lecture from one language to another based on word length.
 *   For each word in the lecture, it finds the corresponding word in the second language
 *   and selects the shorter of the two. In case of equal length, the first language word is preferred.
 * 
 * Algorithms/Techniques:
 *   - Map-based dictionary lookup for efficient word translation
 *   - Input parsing and output formatting
 * 
 * Time Complexity: O(m * log(m) + n)
 *   - Building the map takes O(m * log(m)) due to map insertion
 *   - Translating n words takes O(n) with average O(1) lookup
 * 
 * Space Complexity: O(m * L)
 *   - Where L is the average length of the words, for storing the map
 *   - Additional O(n) for input/output
 */

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::map<std::string, std::string> write; // Map to store word translations
  while (m--) {
    std::string first, second;
    std::cin >> first >> second;
    // If the first language word is not longer than the second, prefer the first
    if (first.size() <= second.size()) {
      second = first;
    }
    // Insert the mapping from first to second language word
    write.insert(std::pair<std::string, std::string>(first, second));
  }
  // Process each word in the lecture
  for (long p = 0; p < n; p++) {
    std::string temp;
    std::cin >> temp;
    // Output the preferred translation
    std::cout << write[temp] << " ";
  }
  puts(""); // Print newline at the end
  return 0;
}


// https://github.com/VaHiX/CodeForces/