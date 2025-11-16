// Problem: CF 1398 B - Substring Removal Game
// https://codeforces.com/contest/1398/problem/B

/* 
B. Substring Removal Game
Purpose: This code solves a game between Alice and Bob where they alternately remove consecutive equal characters from a binary string, aiming to maximize their own score (count of 1s removed). The game is played optimally by both players.
Algorithm: 
- Parse the input string to find all maximal consecutive sequences of '1's.
- Sort these sequence lengths in descending order.
- Sum up every other element starting from index 0 (Alice's turns).
Time Complexity: O(n log n) due to sorting, where n is the length of the string.
Space Complexity: O(n) for storing the vector of sequence lengths.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> v;  // Store lengths of consecutive '1's groups
    long cnt(0);
    bool ones(false);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') {
        ones = true;
        ++cnt;
      } else {
        if (ones) {
          v.push_back(cnt);  // Save the length when we encounter a '0' after '1's
        }
        cnt = 0;
        ones = false;
      }
    }
    if (ones) {
      v.push_back(cnt);  // Handle case where string ends with '1's
    }
    sort(v.rbegin(), v.rend());  // Sort in descending order to prioritize larger groups for Alice

    long total(0);
    for (long p = 0; p < v.size(); p += 2) {
      total += v[p];  // Sum up every other group for Alice's score
    }
    printf("%ld\n", total);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/