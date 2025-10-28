// Problem: CF 2028 A - Alice's Adventures in ''Chess''
// https://codeforces.com/contest/2028/problem/A

/*
Problem: Alice's Adventures in "Chess"
Purpose: Determine if Alice, starting at (0,0), can ever reach the Red Queen at (a,b) using a repeating string of movements.

Algorithm:
- For each test case:
  1. Process input to get string s of length n and target coordinates (a,b).
  2. Compute total displacement (xt, yt) over full cycle of string s.
  3. Check if (0,0) can reach (a,b) in one step directly (no repetition needed).
     Otherwise:
     - Simulate moving through each character of s and check after each move whether
       it's possible to get from current position to (a,b) via multiple cycles of s.
     - Use linear algebra to determine if there exists a non-negative integer k such that:
       (x + k * xt == a) AND (y + k * yt == b)
       which means: (a - x) % xt == 0 and (b - y) % yt == 0,
       and the ratios (a - x)/xt == (b - y)/yt.

Time Complexity: O(n) per test case, where n is the length of the movement string.
Space Complexity: O(1), only using fixed variables regardless of input size.

Input Format:
- t: number of test cases
- n a b: length of movement string and target coordinates
- s: movement string with characters N, E, S, W

Output:
For each test case: "YES" if Alice can meet the Red Queen, otherwise "NO"
*/

#include <iostream>
#include <string>
bool check(long x, long y, long a, long b, long xt, long yt) {
  if (xt == 0 && yt == 0) {
    return x == a && y == b;
  } else if (xt == 0) {
    // Horizontal movement is zero. Vertical must match and be positive multiple.
    return (x == a && (b - y) % yt == 0 && (b - y) / yt > 0);
  } else if (yt == 0) {
    // Vertical movement is zero. Horizontal must match and be positive multiple.
    return (y == b && (a - x) % xt == 0 && (a - x) / xt > 0);
  } else {
    // Both directions have movement. Check alignment of steps in both directions.
    return (a - x) % xt == 0 && (b - y) % yt == 0 && (a - x) / xt >= 0 &&
           (a - x) / xt == (b - y) / yt;
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, a, b;
    std::cin >> n >> a >> b;
    std::string s;
    std::cin >> s;
    long xt(0), yt(0);
    // Compute net displacement over whole sequence
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'N') {
        ++yt;
      } else if (s[p] == 'S') {
        --yt;
      } else if (s[p] == 'E') {
        ++xt;
      } else if (s[p] == 'W') {
        --xt;
      }
    }
    long x(0), y(0);
    bool ans(check(0, 0, a, b, xt, yt));
    // Try all prefixes of sequence to see if we can reach target
    for (long p = 0; p < s.size() && !ans; p++) {
      if (s[p] == 'N') {
        ++y;
      } else if (s[p] == 'S') {
        --y;
      } else if (s[p] == 'E') {
        ++x;
      } else if (s[p] == 'W') {
        --x;
      }
      if (check(x, y, a, b, xt, yt)) {
        ans = true;
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/