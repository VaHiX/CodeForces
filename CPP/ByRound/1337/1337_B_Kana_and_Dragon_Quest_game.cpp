// Problem: CF 1337 B - Kana and Dragon Quest game
// https://codeforces.com/contest/1337/problem/B

#include <cstdio>
// Problem: Kana and Dragon Quest game
// Purpose: Determine if a dragon with x hit points can be defeated using at most n Void Absorptions and m Lightning Strikes.
// Algorithms/Techniques: Greedy approach. Apply Void Absorption when beneficial (x > 20), otherwise use Lightning Strike.
// Time Complexity: O(n + m) per test case, since each spell is applied at most once.
// Space Complexity: O(1), only using a few variables.

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, n, m;
    scanf("%ld %ld %ld", &x, &n, &m);
    // Apply Void Absorption as much as possible while x > 20 and n > 0
    while (n > 0 && x > 20) {
      x = (x / 2) + 10;  // Void Absorption spell: reduce x to floor(x/2) + 10
      --n;
    }
    // Apply Lightning Strike as much as possible while x > 0 and m > 0
    while (m > 0 && x > 0) {
      x -= 10;  // Lightning Strike spell: reduce x by 10
      --m;
    }
    puts(x <= 0 ? "YES" : "NO");  // Output result based on whether dragon is defeated
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/