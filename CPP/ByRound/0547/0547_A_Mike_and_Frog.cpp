// Problem: CF 547 A - Mike and Frog
// https://codeforces.com/contest/547/problem/A

#include <iostream>
using namespace std;
long long m, h1, h2, a1, a2, xx1, xx2, yy1, yy2;
long long t1 = -1, t2 = -1, p = -1, q = -1;
int main() {
  cin >> m >> h1 >> a1 >> xx1 >> yy1 >> h2 >> a2 >> xx2 >> yy2;
  // Simulate the height sequences for both frog and flower up to 2*m steps
  // to detect cycles and find when target heights are reached
  for (long long i = 1; i <= 2 * m; i++) {
    h1 = (h1 * xx1 + yy1) % m; // Update Xaniar's height
    h2 = (h2 * xx2 + yy2) % m; // Update Abol's height
    // Track first occurrence and cycle length of Xaniar reaching target height
    if (h1 == a1) {
      if (p == -1)
        p = i; // First time Xaniar reaches target height
      else if (t1 == -1)
        t1 = i - p; // Cycle length for Xaniar
    }
    // Track first occurrence and cycle length of Abol reaching target height
    if (h2 == a2) {
      if (q == -1)
        q = i; // First time Abol reaches target height
      else if (t2 == -1)
        t2 = i - q; // Cycle length for Abol
    }
  }
  // If either target height is never reached, return -1
  if (p == -1 || q == -1) {
    cout << -1;
    return 0;
  }
  // Find the minimum time when both reach their target heights simultaneously
  for (long long i = 1; i <= 2 * m; i++) {
    if (p == q) {
      cout << p;
      return 0;
    }
    // Advance the smaller time to match the other
    if (p < q)
      p += t1; // Advance Xaniar's time by its cycle
    else
      q += t2; // Advance Abol's time by its cycle
  }
  cout << -1;
  return 0;
}

// **Code Purpose:**
// This code solves the problem of determining the minimum time for two entities
// (a frog and a flower) to reach specific heights under modular arithmetic
// sequences. It simulates their height progression, detects cycles in their
// height sequences, and then uses cycle information to compute the earliest
// time both entities reach their target heights simultaneously.

// **Algorithms/Techniques:**
// - Modular arithmetic simulation
// - Cycle detection in sequences
// - Extended Euclidean or cycle alignment method to find least common time

// **Time Complexity:**
// O(m), where m is the modulus value. The simulation runs for at most 2*m steps
// to detect cycles, and the final alignment loop also runs up to 2*m times.

// **Space Complexity:**
// O(1), as only a constant number of variables are used regardless of input
// size.

// https://github.com/VaHiX/CodeForces/