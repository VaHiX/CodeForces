// Problem: CF 1178 B - WOW Factor
// https://codeforces.com/contest/1178/problem/B

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::string s;
  std::cin >> s;
  s += 'x'; // Add a sentinel to handle the last group of 'v's correctly
  ll w(0), wo(0), h(0), v(0), cnt(0); // w: total 'w's seen so far, wo: sum of w's before current 'o', h: count of 'o's, v: count of consecutive 'v's, cnt: result counter
  for (ll p = 0; p < s.size(); p++) {
    if (s[p] == 'v') {
      ++v; // Increment current group of 'v's
    } else {
      // When we hit an 'o', process the previous group of 'v's
      if (v > 1) {
        cnt += (v - 1) * wo; // Add combinations: (v - 1) ways to pick 2 'v's from current group, multiplied by number of 'w's before this 'o'
        w += (v - 1); // Update total number of 'w's
      }
      if (s[p] == 'o') {
        ++h; // Increment count of 'o's
        wo += w; // Add current total 'w's to the running sum for future 'o's
      }
      v = 0; // Reset current group of 'v's
    }
  }
  std::cout << cnt << std::endl;
  return 0;
}

// https://github.com/VaHiX/codeForces/