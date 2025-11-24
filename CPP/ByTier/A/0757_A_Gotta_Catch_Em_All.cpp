// Problem: CF 757 A - Gotta Catch Em' All!
// https://codeforces.com/contest/757/problem/A

/*
 * Problem: Gotta Catch Em' All!
 * Purpose: Determine how many times the word "Bulbasaur" can be formed from the given string
 *          by using available characters. Each character can only be used once per word.
 * 
 * Algorithm:
 *   1. Count frequency of each required character in "Bulbasaur"
 *   2. Count frequency of each character in input string
 *   3. For each character needed, calculate how many complete words can be made
 *   4. Return minimum of all possible counts
 *
 * Time Complexity: O(n) where n is the length of input string
 * Space Complexity: O(1) since we only store counts for a fixed set of characters (7)
 */

#include <stddef.h>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  std::string s;
  std::cin >> s;
  std::map<char, int> needed;
  std::map<char, int> got;
  needed['B'] = 1;
  needed['u'] = 2;
  needed['l'] = 1;
  needed['b'] = 1;
  needed['a'] = 2;
  needed['s'] = 1;
  needed['r'] = 1;
  got['B'] = 0;
  got['u'] = 0;
  got['l'] = 0;
  got['b'] = 0;
  got['a'] = 0;
  got['s'] = 0;
  got['r'] = 0;
  for (size_t p = 0; p < s.size(); p++) {
    if (got.count(s[p]) == 0) {
      continue;
    }
    ++got[s[p]]; // Count only characters that are needed for "Bulbasaur"
  }
  long count(1e5);
  for (std::map<char, int>::iterator mapIter = got.begin();
       mapIter != got.end(); mapIter++) {
    char key = mapIter->first;
    int have = mapIter->second;
    int need = needed[key];
    // Calculate how many complete words can be made with available characters
    count = (count < (have / need)) ? count : (have / need);
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/