// Problem: CF 975 A - Aramic script
// https://codeforces.com/contest/975/problem/A

/*
 * Purpose: This program determines the number of distinct objects in an Aramic script.
 *          Each object is represented by the "root" of a word, where the root is the
 *          set of unique characters in the word. Since all permutations of a root
 *          represent the same object, we only need to count unique sets of characters.
 *
 * Algorithm:
 *   1. Read the number of words.
 *   2. For each word:
 *      a. Create a set of unique characters (the root).
 *      b. Insert this set into another set to automatically handle duplicates.
 *   3. Output the size of the outer set, which represents the number of distinct objects.
 *
 * Time Complexity: O(n * m * log(m)) where n is the number of words and m is the average
 *                  length of the words. The log(m) factor comes from the insertion into
 *                  the set data structure.
 *
 * Space Complexity: O(n * m) in the worst case where all words have unique character sets.
 */

#include <iostream>
#include <set>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::set<std::set<char>> s;  // Set to store unique character sets (roots)
  while (n--) {
    std::string t;
    std::cin >> t;
    std::set<char> sc;  // Set to store unique characters of current word
    for (long p = 0; p < t.size(); p++) {
      sc.insert(t[p]);  // Insert each character into the set (automatically handles duplicates)
    }
    s.insert(sc);  // Insert the unique character set into the main set
  }
  std::cout << s.size() << std::endl;  // Output the number of distinct objects
  return 0;
}


// https://github.com/VaHiX/CodeForces/