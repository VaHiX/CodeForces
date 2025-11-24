// Problem: CF 1921 B - Arranging Cats
// https://codeforces.com/contest/1921/problem/B

/*
B. Arranging Cats
Time Complexity: O(n) where n is the length of the strings s and f.
Space Complexity: O(1) excluding input storage.

Algorithm:
- For each position i, compare the initial state s[i] with the desired state f[i].
- Count:
  - plus: number of positions where s[i]='1' and f[i]='0' (need to remove a cat)
  - minus: number of positions where s[i]='0' and f[i]='1' (need to add a cat)
- The minimum operations required is the maximum of these two counts.

Techniques:
- Linear scan through the strings
- Greedy approach: we can always pair one removal with one addition,
  so the answer is max(plus, minus).
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string x, y;
    std::cin >> x >> y;
    long minus(0), plus(0);
    for (long p = 0; p < x.size(); p++) {
      if (x[p] == '1' && y[p] == '0') { // Cat needs to be removed
        ++plus;
      } else if (x[p] == '0' && y[p] == '1') { // Cat needs to be added
        ++minus;
      }
    }
    std::cout << (plus > minus ? plus : minus) << std::endl; // Minimum operations needed
  }
}


// https://github.com/VaHiX/codeForces/