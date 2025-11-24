// Problem: CF 1941 D - Rudolf and the Ball Game
// https://codeforces.com/contest/1941/problem/D

// Problem: Rudolf and the Ball Game
// Purpose: Simulate a ball-passing game among n players arranged in a circle, 
//          where each pass can be clockwise ('0'), counterclockwise ('1'), or unknown ('?').
//          Given initial position x and sequence of m moves with directions, 
//          determine all possible final positions of the ball.
//
// Algorithms/Techniques:
// - Set-based simulation: At each step, track all possible current positions using std::set.
// - For each move:
//   - If direction is '0' (clockwise), compute (u + r) % n
//   - If direction is '1' (counterclockwise), compute (n + (u - r) % n) % n
//   - If direction is '?', both possibilities are considered.
//   - Use a set to avoid duplicates.
//
// Time Complexity: O(m * k * log(k)), where k is the maximum possible number of positions.
//                  In worst case, k can be up to n, but often much smaller due to constraints.
// Space Complexity: O(k), for storing the current set of possible positions.

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, x;
    scanf("%ld %ld %ld\n", &n, &m, &x);
    std::set<long> s;
    s.insert(x - 1); // Convert to 0-based indexing
    for (long p = 0; p < m; p++) {
      long r(0);
      char d('?');
      scanf("%ld %c\n", &r, &d);
      std::set<long> w; // New set to store next possible positions
      for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
        const long u = *it;
        if (d == '0' || d == '?') {
          w.insert((u + r) % n);  // Clockwise move
        }
        if (d == '1' || d == '?') {
          w.insert((n + (u - r) % n) % n);  // Counterclockwise move
        }
      }
      s = w; // Update current positions to the new set
    }
    printf("%ld\n", s.size());
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      printf("%ld ", 1 + *it);  // Convert back to 1-based indexing for output
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/