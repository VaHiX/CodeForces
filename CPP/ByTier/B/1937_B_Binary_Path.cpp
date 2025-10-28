// Problem: CF 1937 B - Binary Path
// https://codeforces.com/contest/1937/problem/B

/*
B. Binary Path
Algorithm: Greedy path selection with optimization for lexicographically smallest string.
Time Complexity: O(n) per test case, where n is the length of the row strings.
Space Complexity: O(n) for storing input strings and result substrings.

The problem involves finding a path from top-left (1,1) to bottom-right (2,n) in a 2×n grid,
such that the concatenated binary string of the path is lexicographically minimal.
We use greedy strategy combined with prefix/suffix logic:
- At each step, prefer going right if it leads to a smaller character,
  otherwise go down when necessary.
- Count how many paths yield this minimum string by tracking transitions.

This solution processes each row separately and constructs a minimum path greedily
by comparing characters in each position of row 1 and 2.
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
    std::string a, b;
    std::cin >> a >> b;
    long idx(0), cnt(1), down(n - 1);
    while (idx < n) {
      if (b[idx] < a[idx + 1]) { // If bottom row character is smaller than next in top row
        cnt = 1;                 // Reset path count
        down = idx;              // Set new down position
        break;
      } else if (b[idx] == a[idx + 1]) { // If characters are equal
        down = idx;           // Mark current index as transition point
        while ((idx + 1 < n) && b[idx] == a[idx + 1]) {
          ++idx;
          ++cnt;
        }
        if ((idx == n - 1) || b[idx] < a[idx + 1]) {
          break; // If we reach end or next char is smaller, stop
        } else {
          down = n - 1;
          cnt = 1;
        }
      }
      ++idx;
    }
    std::string mn = a.substr(0, down + 1) + b.substr(down); // Construct lexicographically smallest path string
    std::cout << mn << "\n" << cnt << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/