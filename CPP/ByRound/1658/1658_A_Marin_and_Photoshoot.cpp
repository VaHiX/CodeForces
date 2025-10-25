// Problem: CF 1658 A - Marin and Photoshoot
// https://codeforces.com/contest/1658/problem/A

/*
 * Problem: A. Marin and Photoshoot
 * Algorithm/Techniques: Greedy approach with string manipulation
 * Time Complexity: O(n) where n is the length of the string s
 * Space Complexity: O(1) - only using a few variables for computation
 *
 * Description:
 * Given a binary string representing cosplayers (0 = male, 1 = female),
 * we need to find the minimum number of additional cosplayers to add
 * such that every contiguous segment of at least 2 cosplayers has
 * more females than males.
 *
 * Strategy:
 * We iterate through the string and whenever we encounter a '0',
 * we check its neighbors to decide how many additional females
 * are needed to balance the segment. This greedy approach ensures
 * minimal additions.
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long res(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] != '0') {
        continue; // Skip if not a male
      }
      if (s[p - 1] == '0') {
        res += 2; // If previous is also a male, add two females to make it balanced
      } else if (p > 1 && s[p - 2] == '0') {
        res += 1; // If the one before previous is a male, add one female
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/