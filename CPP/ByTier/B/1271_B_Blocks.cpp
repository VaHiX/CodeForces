// Problem: CF 1271 B - Blocks
// https://codeforces.com/contest/1271/problem/B

/**
 * Problem: Make all blocks the same color using adjacent flips.
 * 
 * Algorithm:
 * 1. Count occurrences of 'W' and 'B'.
 * 2. Determine target color based on parity of counts vs total length.
 * 3. Greedily flip adjacent pairs to achieve target color.
 * 
 * Time Complexity: O(n^2) in worst case due to string modifications
 * Space Complexity: O(n) for storing operations and string
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long b(0), w(0);
  for (long p = 0; p < s.size(); p++) {
    w += (s[p] == 'W');  // Count white blocks
    b += (s[p] == 'B');  // Count black blocks
  }
  char target(0);  // Target color to make all blocks
  if (w % 2 == n % 2) {  // If white count has same parity as total
    target = 'W';
  } else if (b % 2 == n % 2) {  // If black count has same parity as total
    target = 'B';
  }
  std::vector<long> v;  // Store positions of operations
  for (long p = 0; target && p + 1 < s.size(); p++) {
    if (s[p] == target) {
      continue;  // Already correct color
    }
    s[p] = target;  // Set current block to target
    v.push_back(p + 1);  // Record operation (1-indexed)
    if (s[p + 1] == 'W') {
      s[p + 1] = 'B';  // Flip adjacent block
    } else if (s[p + 1] == 'B') {
      s[p + 1] = 'W';  // Flip adjacent block
    }
  }
  if (target) {  // If a target was determined
    std::cout << v.size() << std::endl;
    for (long p = 0; p < v.size(); p++) {
      printf("%ld ", v[p]);
    }
    std::cout << std::endl;
  } else {
    std::cout << "-1" << std::endl;  // Impossible case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/