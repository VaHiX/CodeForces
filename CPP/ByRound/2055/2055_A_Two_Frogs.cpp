// Problem: CF 2055 A - Two Frogs
// https://codeforces.com/contest/2055/problem/A

/*
 * Problem: A. Two Frogs
 * Purpose: Determine if Alice can guarantee a win in a game where two frogs move on lilypads.
 * Algorithm: The key observation is that if the distance between Alice and Bob is odd,
 *            then Alice cannot guarantee a win because the parity of moves will always
 *            leave one player at a disadvantage. If the distance is even, Alice can win.
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1).
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    // If the difference between positions is odd, Alice cannot win
    puts((a - b) % 2 ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/