// Problem: CF 1551 B1 - Wonderful Coloring - 1
// https://codeforces.com/contest/1551/problem/B1

/*
===============================================================================
Problem: B1. Wonderful Coloring - 1
Algorithm/Techniques: Greedy approach with character frequency counting

Time Complexity: O(n) where n is the total length of all strings in the input
Space Complexity: O(1) since we use a fixed-size array of 26 elements regardless of input size

Description:
Given a string, find the maximum number of letters that can be painted red (or green) 
in a "wonderful" coloring. A wonderful coloring satisfies:
1. Each letter is either painted red, green, or unpainted
2. No two letters painted the same color are equal
3. The number of red and green painted letters must be equal
4. The total number of painted letters is maximized

The solution:
- Count frequency of each character
- For each character:
  * If frequency = 1: can be painted in one color (contributes to red or green count)
  * If frequency > 1: can contribute to both colors (only one pair possible per group)
- Each character with frequency > 1 contributes to final count once (as 1 pair)
- Each character with frequency = 1 contributes 1/2 to red count
- So the answer is (number of characters with freq=1) / 2 + (number of characters with freq>1)

===============================================================================
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt[26] = {0}; // Array to store frequency of each character (a-z)
    for (long p = 0; p < s.size(); p++) {
      ++cnt[s[p] - 'a']; // Increment count for current character
    }
    long x(0), y(0); // x: characters with frequency 1, y: characters with frequency > 1
    for (long p = 0; p < 26; p++) {
      if (cnt[p] == 1) {
        ++x; // Count character that appears only once
      } else if (cnt[p] > 1) {
        ++y; // Count character that appears more than once
      }
    }
    std::cout << (x / 2 + y) << std::endl; // Calculate maximum red letters possible
  }
}


// https://github.com/VaHiX/codeForces/