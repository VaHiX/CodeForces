// Problem: CF 2094 D - Tung Tung Sahur
// https://codeforces.com/contest/2094/problem/D

/*
 * Problem: Determine if a given sound string s could be the result of hits from a pattern string p.
 *          Each hit in p can produce either one or two sounds (e.g., "L" -> "L" or "LL").
 *
 * Algorithm:
 * 1. For both strings p and s, compress them into runs of consecutive characters with their counts.
 * 2. Compare the compressed forms:
 *    - The sequence of characters must match.
 *    - For each character, the count in s must be between half and double the count in p.
 *    - If these conditions are violated, then s is not a valid sound from p.
 *
 * Time Complexity: O(n + m) where n = |p|, m = |s|
 * Space Complexity: O(n + m) for storing the compressed representations
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    a += '_';  // Add sentinel to simplify loop
    b += '_';
    std::vector<std::pair<char, long>> va, vb;  // Compressed runs for a and b
    long cnt(1);
    for (long p = 1; p < a.size(); p++) {
      if (a[p - 1] == a[p]) {
        ++cnt;
      } else {
        va.push_back(std::make_pair(a[p - 1], cnt));  // Store character and count
        cnt = 1;
      }
    }
    cnt = 1;
    for (long p = 1; p < b.size(); p++) {
      if (b[p - 1] == b[p]) {
        ++cnt;
      } else {
        vb.push_back(std::make_pair(b[p - 1], cnt));  // Store character and count
        cnt = 1;
      }
    }
    bool res(true);
    if (va.size() != vb.size()) {  // Different number of runs
      res = false;
    }
    for (long p = 0; res && p < va.size(); p++) {
      if (va[p].first != vb[p].first) {  // Characters don't match
        res = false;
      }
      if (vb[p].second < va[p].second || vb[p].second > 2 * va[p].second) {  // Count constraint violated
        res = false;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/