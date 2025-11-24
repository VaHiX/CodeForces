// Problem: CF 1873 D - 1D Eraser
// https://codeforces.com/contest/1873/problem/D

/*
D. 1D Eraser
Algorithm: Greedy
Time Complexity: O(n) - Each character is visited at most once.
Space Complexity: O(1) - Only a few variables are used, no extra space proportional to input size.

Task: Given a string of 'B' and 'W', find the minimum number of operations to turn all 'B's into 'W's,
where each operation covers k consecutive cells and turns them all to 'W'.

Approach:
- Traverse the string from left to right.
- Whenever we encounter a 'B', we perform an operation starting at that position.
- This greedy strategy ensures we cover as many 'B's as possible with each operation.
- Increment operation count and jump ahead by k positions.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;  // Read length of string and operation size
    std::string s;
    std::cin >> s;  // Read the string
    long cnt(0), idx(0);  // cnt: number of operations, idx: current position in string
    while (idx < s.size()) {
      if (s[idx] == 'B') {  // If we find a black cell
        ++cnt;  // Increment operation count
        idx += k;  // Move index by k to skip the next k positions (as they are now white)
      } else {
        ++idx;  // Otherwise, move to next character
      }
    }
    std::cout << cnt << std::endl;  // Output number of operations needed
  }
}


// https://github.com/VaHiX/codeForces/