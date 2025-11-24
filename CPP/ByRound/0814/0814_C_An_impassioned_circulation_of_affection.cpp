// Problem: CF 814 C - An impassioned circulation of affection
// https://codeforces.com/contest/814/problem/C

/*
Purpose: This code solves the problem of maximizing the "Koyomity" of a garland after repainting at most m pieces to a target color c.
         Koyomity is defined as the length of the longest contiguous subsegment of the garland that consists only of the color c.
         The approach involves precomputing for each possible color, the maximum length of a subsegment of that color achievable by repainting up to k pieces.

Algorithms/Techniques:
- Dynamic Programming with precomputed subsegment lengths
- Two-pass preprocessing to handle all repaint counts up to n for each color
- Efficiently computes optimal subsegments for each color using sliding window-like approach

Time Complexity: O(N^2 * C) where N is the length of the garland and C is the number of letters (26)
Space Complexity: O(N * C) for storing the precomputed results for each color and repaint count
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 26;
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  // t[letter][count] stores the maximum length of a subsegment of color 'letter' using 'count' repaints
  std::vector<std::vector<long>> t(N, std::vector<long>(n + 1, -1));
  for (int letter = 0; letter < N; letter++) {
    for (long p = 0; p < n; p++) {
      long count(0);
      for (long q = p; q < n; q++) {
        // Count how many characters differ from the target letter
        count += (s[q] != ('a' + letter));
        long length = q - p + 1;
        // Update the maximum length for this count
        t[letter][count] =
            (t[letter][count] > length) ? t[letter][count] : length;
      }
    }
  }
  // Propagate the maximum lengths for all counts (from 0 to n)
  for (int letter = 0; letter < N; letter++) {
    for (long p = 1; p < t[letter].size(); p++) {
      if (t[letter][p] < 0) {
        t[letter][p] = t[letter][p - 1];
      }
    }
  }
  long q;
  std::cin >> q;
  while (q--) {
    long m;
    char c;
    std::cin >> m >> c;
    std::cout << t[c - 'a'][m] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/