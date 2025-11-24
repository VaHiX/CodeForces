// Problem: CF 628 C - Bear and String Distance
// https://codeforces.com/contest/628/problem/C

/*
 * Problem: Bear and String Distance
 * Algorithm/Technique: Greedy string construction
 * 
 * Time Complexity: O(n), where n is the length of the string
 * Space Complexity: O(n), for storing the result string
 * 
 * Approach:
 * - For each character in the input string, we decide whether to change it 
 *   to 'a' or 'z' based on which gives a larger distance (greedily).
 * - We use a greedy approach to maximize the distance by choosing the 
 *   character that gives the maximum possible contribution to the total distance.
 * - If the total achievable distance is less than k, return -1.
 * - Otherwise, adjust the last character to make the distance exactly k.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  std::string t;
  t = s;
  for (long p = 0; p < s.size(); p++) {
    char c = s[p];
    int da = c - 'a';    // Distance to 'a'
    int dz = 'z' - c;    // Distance to 'z'
    int d = (da > dz) ? da : dz;  // Maximum possible distance for this character
    char x = (da > dz) ? 'a' : 'z';  // Character that gives max distance
    if (d < k) {
      t[p] = x;
      k -= d;  // Use up the maximum possible distance
    } else {
      // If we can't use the full max distance, adjust the current character
      t[p] = s[p] + (da > dz ? (-1) : 1) * k;
      k = 0;
      break;
    }
  }
  if (k) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << t << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/