// Problem: CF 1077 A - Frog Jumping
// https://codeforces.com/contest/1077/problem/A

/*
 * Problem: Frog Jumping
 * Algorithms/Techniques: Mathematical pattern recognition, modular arithmetic
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 *
 * A frog starts at position 0 and alternates between jumping 'a' units right and 'b' units left.
 * The pattern repeats every two jumps: right by 'a', then left by 'b'.
 * For k jumps:
 *   - If k is even, there are exactly k/2 full cycles of (a - b)
 *   - If k is odd, there are (k/2) full cycles plus one more jump to the right by 'a'
 * This allows us to compute the final position directly without simulating all jumps.
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll a, b, k; // jump lengths and number of jumps
    scanf("%lld %lld %lld", &a, &b, &k);
    
    // Calculate result using pattern:
    // Each pair of jumps contributes (a - b) to the position.
    // If k is odd, we add one more 'a' for the final rightward jump.
    ll res = (a - b) * (k / 2) + a * (k % 2);
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/