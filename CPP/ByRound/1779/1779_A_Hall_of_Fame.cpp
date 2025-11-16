// Problem: CF 1779 A - Hall of Fame
// https://codeforces.com/contest/1779/problem/A

/*
Algorithm: Greedy
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) as only a constant amount of extra space is used

The problem requires determining whether we can illuminate all trophies by either:
1. Doing nothing (if already possible)
2. Swapping two adjacent lamps once (if that helps)

Key observations:
- A lamp 'L' at position i illuminates trophies from 1 to i-1.
- A lamp 'R' at position i illuminates trophies from i+1 to n.
- If the string is all 'L's or all 'R's, it's impossible to illuminate all trophies.
- We can try a swap if there's an 'R' followed by an 'L' or 'L' followed by an 'R' that would help.

Approach:
1. First, check if all trophies are already illuminated.
2. If not, find a valid swap that helps illuminate all trophies.
3. We prioritize a specific swap that makes one lamp illuminate more trophies, and we try to do it greedily.
4. For each adjacent pair, we look for patterns that would improve illumination.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long res(-1);
    // First loop: check if there's an 'R' followed by 'L'
    // This means when swapped, it might help illuminate some trophy
    for (long p = 1; (res < 0) && p < n; p++) {
      if (s[p - 1] == 'R' && s[p] == 'L') {
        res = 0; // No swap needed if this pattern exists, but set to 0 to indicate not doing any
        break;
      }
    }
    // Second loop: check for 'L' followed by 'R'
    // If we swap, it can potentially make both lamps cover trophies on both sides
    for (long p = 1; (res < 0) && p < n; p++) {
      if (s[p - 1] == 'L' && s[p] == 'R') {
        res = p; // Index of the first lamp in the pair to be swapped (1-based)
        break;
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/